#pragma once

#include <string>
#include <memory>

#include <Core/Resource.h>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A ShaderObject represents a single programmable stage in a render pipeline.
		 *
		 */
		class ShaderObject : public Resource
		{
		public:
			//! All possible types of shader objects
			enum ShaderType
			{
				INVALID_SHADER = 0,
				VERTEX_SHADER,
				TESS_CONTROL_SHADER,
				TESS_EVALUATION_SHADER,
				GEOMETRY_SHADER,
				FRAGMENT_SHADER,
				COMPUTE_SHADER,
				NUM_SHADER_TYPES
			};

			//! Load and creates a shader object from file. File extension determines shader type.
			static std::shared_ptr<ShaderObject> load(const fs::path& fsPath);

			//! Creates, compiles and returns a shader object from source.
			static std::shared_ptr<ShaderObject> create(const std::string& sShaderSource, ShaderType eType);

			//! Destructor.
			virtual ~ShaderObject();

			//! Set shader name.
			void setName(const std::string& sName) { m_sName = sName; }
			//! Get shader name.
			std::string getName() const { return m_sName; }
			//! Get the shader source.
			std::string getSource() const { return m_sSource; }
			//! Get the shader type.
			ShaderType getType() const { return m_eType; }
			//! Get shader ID.
			unsigned int getID() const { return m_uID; }

			//! Resource type override
			virtual std::string getResourceType() const { return "ShaderObject"; }

		protected:
			//! Protected constructor - must be created by static create().
			ShaderObject(const std::string& sName, ShaderType eType, unsigned int iID, const std::string& sSource);

		private:
			std::string m_sName;	//!< Shader name.
			std::string m_sSource;	//!< The shader object source code.
			ShaderType m_eType;	//!< Type of shader object.
			unsigned int m_uID;		//!< Shader object ID.
		};
	}
}