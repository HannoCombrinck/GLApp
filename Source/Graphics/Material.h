#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Shader;
		class Texture;
		class RenderState;
	}
}

namespace baselib 
{
	namespace graphics
	{
		class Material
		{
		public:
			//! Constructor.
			Material();
			//! Destructor.
			~Material();

			//! Set the shader instance.
			void setShader(const boost::shared_ptr<Shader>& spShader) { m_spShader = spShader; }
			//! Getter for setShader().
			boost::shared_ptr<Shader> getShader() const { return m_spShader; }

			//! Set the texture.
			void setTexture(const boost::shared_ptr<Texture>& spTexture) { m_spTexture = spTexture; }
			//! Getter for setTexture().
			boost::shared_ptr<Texture> getTexture() const { return m_spTexture; }

			//! Set the render state.
			void setRenderState(const boost::shared_ptr<RenderState>& spRenderState) { m_spRenderState = spRenderState; }
			//! Getter for setRenderState().
			boost::shared_ptr<RenderState> getRenderState() const { return m_spRenderState; }
		
		private:
			boost::shared_ptr<Shader> m_spShader;			//!< Shader used by this material.
			boost::shared_ptr<Texture> m_spTexture;			//!< Texture used by this material.
			boost::shared_ptr<RenderState> m_spRenderState;	//!< Render state associated with this material.

		};
	}
}