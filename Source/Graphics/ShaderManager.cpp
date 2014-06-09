#include "ShaderManager.h"

#include <GL/glew.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <Logging/Log.h>
#include <Graphics/ShaderPipeline.h>

namespace baselib { namespace graphics {

	namespace
	{
		boost::unordered_map<std::string, unsigned int> aShaderExtensionMap;
		boost::unordered_map<unsigned int, std::pair<std::string, unsigned int>> aShaderTypeMap;

		void registerShader(unsigned int uType, const std::string& sType, const std::string& sExtension, unsigned int uGLType)
		{
			aShaderExtensionMap[sExtension] = uType;
			aShaderTypeMap[uType] = std::make_pair(sType, uGLType);
		}

		unsigned int getTypeFromExtension(const std::string& sExtension) { return aShaderExtensionMap[sExtension]; }
		unsigned int getGLShaderType(unsigned int uType) { return aShaderTypeMap[uType].second;	}
		std::string getShaderTypeString(unsigned int uType) { return aShaderTypeMap[uType].first; }
	}

	ShaderManager::ShaderManager()
	{
		LOG_VERBOSE << "ShaderManager constructor";

		registerShader(ShaderObject::VERTEX_SHADER,		     "vertex",				    ".vert", GL_VERTEX_SHADER);
		registerShader(ShaderObject::TESS_CONTROL_SHADER,    "tessellation control",    ".tesc", GL_TESS_CONTROL_SHADER);
		registerShader(ShaderObject::TESS_EVALUATION_SHADER, "tessellation evaluation", ".tese", GL_TESS_EVALUATION_SHADER);
		registerShader(ShaderObject::GEOMETRY_SHADER,		 "geometry",				".geom", GL_GEOMETRY_SHADER);
		registerShader(ShaderObject::FRAGMENT_SHADER,		 "fragment",				".frag", GL_FRAGMENT_SHADER);
		registerShader(ShaderObject::COMPUTE_SHADER,		 "compute",					".comp", GL_COMPUTE_SHADER);
	}

	ShaderManager::~ShaderManager()
	{
		LOG_VERBOSE << "ShaderManager destructor";
	}

	namespace
	{
		// Loads source code from a text file into sSource string.
		std::string loadSourceFromFile(const fs::path& fsPath)
		{
			fs::ifstream inFile(fsPath);
			if (!inFile.is_open())
			{
				LOG_ERROR << "Failed to open file " << fsPath;
				assert(false);
			}

			std::string sSource;
			sSource.assign(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());

			inFile.close();
			return sSource;
		}
		
		// Check for valid shader object combinations.
		bool isValidPipeline(const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects)
		{
			bool bValid = true;

			// Count number of shader objects per type.
			int iCount[ShaderObject::NUM_SHADER_TYPES];
			memset(iCount, 0, sizeof(int) * ShaderObject::NUM_SHADER_TYPES);

			boost::for_each(aspShaderObjects, [&iCount, &bValid](const boost::shared_ptr<ShaderObject>& spShaderObject) {
				unsigned int uType = spShaderObject->getType();

				if (uType < 0 || uType >= ShaderObject::NUM_SHADER_TYPES)
				{
					LOG_ERROR << "Shader object has invalid type";
					assert(false);
				}
				
				iCount[uType] += 1;

				if (iCount[uType] > 1)
				{
					LOG_ERROR << "Only one shader object of each type is allowed per shader pipeline.";
					bValid = false;
					return;
				}
			});

			// TODO: Check for valid shader object combiations

			//if (iCount[ShaderObject::VERTEX_SHADER] != 1)
			//	bValid = false;
			
			return bValid;
		}
	}

	boost::shared_ptr<ShaderPipeline> ShaderManager::createShaderPipeline(const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects)
	{
		if (!isValidPipeline(aspShaderObjects))
		{
			LOG_ERROR << "Trying to create shader pipeline with invalid combination of shader objects.";
			assert(false);
		}

		LOG_ERROR << "TODO: Create ShaderPipeline object";
		assert(false);
		return boost::shared_ptr<ShaderPipeline>();
	}

	boost::shared_ptr<ShaderObject> ShaderManager::createShaderObject(const fs::path& fsPath)
	{
		// Check if shader object already exists
		auto iter = m_aShaderObjectMap.find(fs::canonical(fsPath).string());
		if (iter != m_aShaderObjectMap.end())
		{
			LOG_VERBOSE << fsPath << " shader object already loaded.";
			if (auto sp = iter->second.lock())
			{
				LOG_VERBOSE << "Returning reference to existing shader object";
				return sp;
			}
			else
			{
				LOG_VERBOSE << fsPath << " doesn't exist anymore. Removing from manager and reloading from file.";
				m_aShaderObjectMap.erase(iter);
			}
		}

		// Check if file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find shader source file " << fsPath;
			assert(false);
		}

		// Check if file has extension
		if (!fsPath.has_extension())
		{
			LOG_ERROR << "Shader source file " << fsPath << " does not have an extension.";
			assert(false);
		}
		
		// Get shader type from extension
		std::string sExtension = fsPath.extension().string();
		auto uType = getTypeFromExtension(sExtension);
		
		// Check for valid extension
		if (uType == ShaderObject::INVALID_SHADER)
		{
			LOG_ERROR << "Invalid shader source file extension: " << sExtension << "\nValid extensions are:\n.vert\n.tesc\n.tese\n.geom\n.frag\n.comp";
			assert(false);
		}

		// Load the shader source from file
		std::string sSource = loadSourceFromFile(fsPath);

		LOG_INFO << "Loading shader from file: " << fsPath;

		auto spShaderObject = createShaderObject(sSource, uType);
		spShaderObject->setName(fs::canonical(fsPath).string());
		m_aShaderObjectMap[spShaderObject->getName()] = spShaderObject; // Add to shader map
		return spShaderObject;
	}

	boost::shared_ptr<ShaderObject> ShaderManager::createShaderObject(const std::string& sShaderSource, unsigned int uType)
	{
		// Get GL shader type
		unsigned int uGLShaderType = getGLShaderType(uType);

		// Get shader type as a string
		std::string sShaderType = getShaderTypeString(uType);

		// Create the shader
		LOG_INFO << "Creating " << sShaderType << " shader...";
		unsigned int uShaderObjectID = glCreateShader(uGLShaderType);

		// Commit the shader source to compiler
		const char* szShaderSource = sShaderSource.c_str();
		glShaderSource(uShaderObjectID, 1, (const char**)&szShaderSource, NULL);

		// Compile the shader
		LOG_INFO << "Compiling " << sShaderType << " shader...";
		glCompileShader(uShaderObjectID);

		// Get GLSL compiler status
		int iCompileStatus = 0;
		glGetShaderiv(uShaderObjectID, GL_COMPILE_STATUS, &iCompileStatus);
		if (iCompileStatus == GL_TRUE)
		{
			LOG_INFO << "Successfully compiled " << sShaderType << " shader.";
		}
		else
		{
			LOG_ERROR << "Failed to compile " << sShaderType << " shader.";
			glDeleteShader(uShaderObjectID);
			uShaderObjectID = ~0;
			// Assert after logging GLSL compiler errors
		}

		// Get GLSL compiler log
		int iLogLength = 0;
		glGetShaderiv(uShaderObjectID, GL_INFO_LOG_LENGTH, &iLogLength);
		char *szLog = new char[iLogLength + 1];
		glGetShaderInfoLog(uShaderObjectID, iLogLength, NULL, szLog);
		std::string sCompilerLog(szLog);
		delete[] szLog;

		LOG_INFO << sCompilerLog;

		assert(iCompileStatus == GL_TRUE);

		auto spShaderObject = boost::shared_ptr<ShaderObject>(new ShaderObject("", uType, uShaderObjectID, sShaderType));
		return spShaderObject;
	}

} }