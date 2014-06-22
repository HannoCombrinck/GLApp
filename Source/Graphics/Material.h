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
		/*! @brief A Material encapsulates shader(s), texture(s) and render state.
		 *
		 */
		class Material
		{
		public:
			//! Constructor.
			Material(const boost::shared_ptr<Shader>& spShader, const boost::shared_ptr<Texture>& spTexture, const boost::shared_ptr<RenderState>& spRenderState);
			//! Destructor.
			virtual ~Material();

			//! Getter for setShader().
			boost::shared_ptr<Shader> getShader() const { return m_spShader; }
			//! Getter for setTexture().
			boost::shared_ptr<Texture> getTexture() const { return m_spTexture; }
			//! Getter for setRenderState().
			boost::shared_ptr<RenderState> getRenderState() const { return m_spRenderState; }
		
		private:
			boost::shared_ptr<Shader> m_spShader;			//!< Shader used by this material.
			boost::shared_ptr<Texture> m_spTexture;			//!< Texture used by this material.
			boost::shared_ptr<RenderState> m_spRenderState;	//!< Render state associated with this material.

		};
	}
}