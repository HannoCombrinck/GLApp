#pragma once

#include <string>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A ShaderObject represents a single programmable stage in a render pipeline.
		 *
		 */
		class ShaderObject
		{
		public:
			friend class ShaderManager;

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
			virtual ~ShaderObject();

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

		protected:
			//! Protected constructor - must be created by ShaderManager.
			ShaderObject(const std::string& sName, unsigned int uType, unsigned int iID, const std::string& sSource);

		private:
			std::string m_sName;	//!< Shader name.
			std::string m_sSource;	//!< The shader object source code.
			unsigned int m_uType;	//!< Type of shader object.
			unsigned int m_uID;		//!< Shader object ID.
		};
	}
}