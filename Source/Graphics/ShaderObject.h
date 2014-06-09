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
				INVALID_SHADER = 0,
				VERTEX_SHADER,
				TESS_CONTROL_SHADER,
				TESS_EVALUATION_SHADER,
				GEOMETRY_SHADER,
				FRAGMENT_SHADER,
				COMPUTE_SHADER,
				NUM_SHADER_TYPES
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
			unsigned int getType() const { return m_uType; }
			//! Get shader ID.
			unsigned int getID() const { return m_uID; }

		private:
			friend class ShaderManager;
			//! Private constructor - must be created using ShaderManager.
			ShaderObject(const std::string& sName, unsigned int uType, unsigned int iID, const std::string& sSource);

			std::string m_sName;	//!< Shader name.
			std::string m_sSource;	//!< The shader object source code.
			unsigned int m_uType;	//!< Type of shader object.
			unsigned int m_uID;		//!< Shader object ID.
		};
	}
}