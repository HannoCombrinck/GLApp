#include "ShaderFactory.h"

#include <GL/glew.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <Logging/Log.h>
#include <Graphics/ShaderPipeline.h>

namespace baselib { namespace graphics {

	namespace
	{
		boost::unordered_map<std::string, ShaderObject::ShaderType> aShaderExtensionMap;
		boost::unordered_map<ShaderObject::ShaderType, std::pair<std::string, unsigned int>> aShaderTypeMap;

		void registerShader(ShaderObject::ShaderType eType, const std::string& sType, const std::string& sExtension, unsigned int uGLType)
		{
			aShaderExtensionMap[sExtension] = eType;
			aShaderTypeMap[eType] = std::make_pair(sType, uGLType);
		}

		ShaderObject::ShaderType getTypeFromExtension(const std::string& sExtension) { return aShaderExtensionMap[sExtension]; }
		unsigned int getGLShaderType(ShaderObject::ShaderType eType) { return aShaderTypeMap[eType].second;	}
		std::string getShaderTypeString(ShaderObject::ShaderType eType) { return aShaderTypeMap[eType].first; }
	}

	ShaderFactory::ShaderFactory()
	{
		LOG_VERBOSE << "ShaderFactory constructor";

		registerShader(ShaderObject::VERTEX_SHADER,		     "vertex",				    ".vert", GL_VERTEX_SHADER);
		registerShader(ShaderObject::TESS_CONTROL_SHADER,    "tessellation control",    ".tesc", GL_TESS_CONTROL_SHADER);
		registerShader(ShaderObject::TESS_EVALUATION_SHADER, "tessellation evaluation", ".tese", GL_TESS_EVALUATION_SHADER);
		registerShader(ShaderObject::GEOMETRY_SHADER,		 "geometry",				".geom", GL_GEOMETRY_SHADER);
		registerShader(ShaderObject::FRAGMENT_SHADER,		 "fragment",				".frag", GL_FRAGMENT_SHADER);
		registerShader(ShaderObject::COMPUTE_SHADER,		 "compute",					".comp", GL_COMPUTE_SHADER);
	}

	ShaderFactory::~ShaderFactory()
	{
		LOG_VERBOSE << "ShaderFactory destructor";
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
				ShaderObject::ShaderType eType = spShaderObject->getType();

				if (eType < 0 || eType >= ShaderObject::NUM_SHADER_TYPES)
				{
					LOG_ERROR << "Shader object has invalid type";
					assert(false);
				}
				
				iCount[eType] += 1;

				if (iCount[eType] > 1)
				{
					LOG_ERROR << "Only one shader object of each type is allowed per shader pipeline";
					bValid = false;
					return;
				}
			});

			// TODO: Check for valid shader object combinations

			//if (iCount[ShaderObject::VERTEX_SHADER] != 1)
			//	bValid = false;
			
			return bValid;
		}
	}

	boost::shared_ptr<ShaderPipeline> ShaderFactory::createShaderPipeline(const std::string& sName, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects)
	{
		if (!isValidPipeline(aspShaderObjects))
		{
			LOG_ERROR << "Trying to create shader pipeline with invalid combination of shader objects";
			assert(false);
		}

		// Create shader program
		LOG_INFO << "Creating shader pipeline: " << sName;
		unsigned int uShaderProgramID = glCreateProgram();
		assert(uShaderProgramID);

		// Attach shader objects
		LOG_VERBOSE << "Attaching shader objects to pipeline";
		boost::for_each(aspShaderObjects, [&uShaderProgramID](const boost::shared_ptr<ShaderObject>& spShaderObject) {
			glAttachShader(uShaderProgramID, spShaderObject->getID());
		});

		// Link shader program
		LOG_VERBOSE << "Linking shader pipeline";
		glLinkProgram(uShaderProgramID);

		// Detach shader objects for release build only.
		// After linking a shader program the shader objects can be detached and are no longer needed.
		// Keeping them attached, and alive, is useful for debugging purposes though.
		// gDEBugger can, for example, rebuild and relink programs on the fly if they remain attached.
		#ifndef _DEBUG
		boost::for_each(aspShaderObjects, [&uShaderProgramID](const boost::shared_ptr<ShaderObject>& spShaderObject) {
			glDetachShader(uShaderProgramID, spShaderObject->getID());
		});
		#endif

		// Get linker status
		int iLinkStatus = 0;
		glGetProgramiv(uShaderProgramID, GL_LINK_STATUS, &iLinkStatus);

		// Get linker log
		int iLogLength = 0;
		glGetProgramiv(uShaderProgramID, GL_INFO_LOG_LENGTH, &iLogLength);
		char *szLog = new char[iLogLength + 1];
		glGetProgramInfoLog(uShaderProgramID, iLogLength, NULL, szLog);
		std::string sLinkerLog(szLog);
		delete[] szLog;

		if (!sLinkerLog.empty())
			LOG_INFO << sLinkerLog;

		// Check linker status
		if (iLinkStatus == GL_FALSE)
		{
			LOG_ERROR << "Failed to link shader pipeline";
			glDeleteProgram(uShaderProgramID);
			assert(false);
		}

		// Let the ShaderPipeline keep the shader objects alive for debug configurations. For release
		// configurations let them go out of scope and destroy the hardware buffers which are no longer required.
		#ifdef _DEBUG
		return boost::shared_ptr<ShaderPipeline>(new ShaderPipeline(sName, uShaderProgramID, aspShaderObjects));
		#else
		return boost::shared_ptr<ShaderPipeline>(new ShaderPipeline(sName, uShaderProgramID));
		#endif
	}

	boost::shared_ptr<ShaderObject> ShaderFactory::createShaderObject(const fs::path& fsPath)
	{
		// Check if file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find shader source file " << fsPath;
			assert(false);
		}

		// Get canonical path
		std::string sCanonicalPath = fs::canonical(fsPath).string();

		// If shader object is already cached just return it
		if (auto sp = m_ShaderCache.get(sCanonicalPath))
			return sp;

		// Check if file has an extension
		if (!fsPath.has_extension())
		{
			LOG_ERROR << "Shader source file " << sCanonicalPath << " does not have an extension";
			assert(false);
		}
		
		// Get shader type from extension
		std::string sExtension = fsPath.extension().string();
		auto eType = getTypeFromExtension(sExtension);
		
		// Check for valid type
		if (eType == ShaderObject::INVALID_SHADER)
		{
			LOG_ERROR << "Invalid shader source file extension: " << sExtension << "\nValid extensions are:\n.vert\n.tesc\n.tese\n.geom\n.frag\n.comp";
			assert(false);
		}

		// Load the shader source from file and create the shader object
		LOG_INFO << "Loading: " << sCanonicalPath;
		std::string sSource = loadSourceFromFile(sCanonicalPath);
		auto spShaderObject = createShaderObject(sSource, eType);
		spShaderObject->setName(fsPath.string());

		// Cache the shader object
		m_ShaderCache.add(sCanonicalPath, spShaderObject);

		return spShaderObject;
	}

	boost::shared_ptr<ShaderObject> ShaderFactory::createShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType)
	{
		// Get GL shader type
		unsigned int uGLShaderType = getGLShaderType(eType);

		// Get shader type as a string
		std::string sShaderType = getShaderTypeString(eType);

		// Create the shader
		LOG_VERBOSE << "Creating " << sShaderType << " shader";
		unsigned int uShaderObjectID = glCreateShader(uGLShaderType);
		assert(uShaderObjectID);

		// Commit the shader source to compiler
		const char* szShaderSource = sShaderSource.c_str();
		glShaderSource(uShaderObjectID, 1, (const char**)&szShaderSource, NULL);

		// Compile the shader
		LOG_INFO << "Compiling " << sShaderType << " shader";
		glCompileShader(uShaderObjectID);

		// Get GLSL compiler status
		int iCompileStatus = 0;
		glGetShaderiv(uShaderObjectID, GL_COMPILE_STATUS, &iCompileStatus);
		if (iCompileStatus == GL_TRUE)
		{
			LOG_VERBOSE << "Successfully compiled " << sShaderType << " shader";
		}
		else
		{
			LOG_ERROR << "Failed to compile " << sShaderType << " shader";
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

		if (!sCompilerLog.empty())
			LOG_INFO << sCompilerLog;

		assert(iCompileStatus == GL_TRUE);

		return boost::shared_ptr<ShaderObject>(new ShaderObject("", eType, uShaderObjectID, sShaderSource));;
	}

} }