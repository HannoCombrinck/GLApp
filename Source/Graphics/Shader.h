#pragma once

#include <string>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A Shader is an instance of a ShaderPipeline.
		 *
		 *  A Shader has unique uniforms, textures etc. but can be an instance 
		 *  of the same pipeline as other Shaders (i.e. share the shader program ID).
		 */
		class Shader
		{
		public:
			friend class ShaderPipeline;

			//! Destructor.
			virtual ~Shader();

			//! Get shader ID.
			unsigned int getID() const { return m_uID; }

			//! Get attribute index from name.
			int getAttribute(const std::string& sName) const;
			//! Get uniform index from name.
			int getUniform(const std::string& sName) const;
		
			// TODO: Add all setUniform* and setAttribute* functions

		protected:
			//! Protected constructor - must be created by ShaderPipeline.
			Shader(unsigned int uID);

		private:
			unsigned int m_uID; //!< Shader program ID.
			
		};
	}
}