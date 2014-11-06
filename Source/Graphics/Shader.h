#pragma once

#include <string>
#include <Math/Math.h>
#include <boost/shared_ptr.hpp>

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

			//! Bind shader.
			void bind();

			//! Get shader ID.
			unsigned int getID() const { return m_uID; }

			//! Get attribute index from name.
			int getAttribute(const std::string& sName) const;
			//! Get uniform index from name.
			int getUniform(const std::string& sName) const;
			//! Get uniform index from name and return true if the uniform exists.
			bool getUniform(int& iIndex, const std::string& sName) const;
		
			//! Set float uniform variable.
			void setUniform(int iIndex, float f);
			//! Set vec2f uniform variable.
			void setUniform(int iIndex, const Vec2& v);
			//! Set vec3f uniform variable.
			void setUniform(int iIndex, const Vec3& v);
			//! Set vec4f uniform variable.
			void setUniform(int iIndex, const Vec4& v);
			//! Set mat4f uniform variable.
			void setUniform(int iIndex, const Mat4& m);
			//! Set mat4f uniform if it exists.
			void setUniform(const std::string& sName, const Mat4& m);
			//! Set int uniform variable.
			void setUniform(int iIndex, int i);
			//! Set int uniform if it exists.
			void setUniform(const std::string& sName, int i);
			
		protected:
			//! Protected constructor - must be created by ShaderPipeline.
			Shader(const boost::shared_ptr<ShaderPipeline>& spShaderPipeline);

		private:
			static unsigned int m_uCurrentlyBound; //!< Currently bound shader.

			boost::shared_ptr<ShaderPipeline> m_spShaderPipeline; //!< The pipeline that this instanced was created from
			unsigned int m_uID; //!< Shader program ID.
			
		};
	}
}