#pragma once

#include <string>

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

			//! Constructor
			ShaderObject(const std::string& sSource, ShaderType eType);
			//! Destructor
			~ShaderObject();

			//! Compile source and create shader object.
			void init();
			//! Get the shader object source.
			std::string GetSource() const { return m_sSource; }
			//! Get the type of the shader object.
			ShaderType GetType() const { return m_eType; }
			//! Get the shader object ID.
			unsigned int GetID() const { return m_uID; }

		private:
			std::string m_sSource; //!< The shader object source code.
			ShaderType m_eType;	   //!< Type of shader object.
			unsigned int m_uID;	   //!< Uniqe shader object ID.
		};
	}
}