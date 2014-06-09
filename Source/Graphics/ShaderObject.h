#pragma once

#include <string>
#include <boost/weak_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class ShaderObject
		{
		public:
			//! All possible types of shader objects
			enum ShaderType
			{
				VERTEX_SHADER,
				TESS_CONTROL_SHADER,
				TESS_EVALUATION_SHADER,
				GEOMETRY_SHADER,
				FRAGMENT_SHADER,
				COMPUTE_SHADER,
				INVALID_SHADER
			};

			//! Destructor.
			~ShaderObject();

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

		private:
			friend class ShaderManager;
			//! Private constructor - must be created using ShaderManager.
			ShaderObject(const std::string& sName, ShaderType eType, unsigned int iID, const std::string& sSource);

			std::string m_sName;	//!< Shader name.
			std::string m_sSource;	//!< The shader object source code.
			ShaderType m_eType;		//!< Type of shader object.
			unsigned int m_uID;		//!< Uniqe ID.
		};
	}
}