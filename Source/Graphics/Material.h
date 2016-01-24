#pragma once

#include <memory>

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
			//! Creates a Material.
			static std::shared_ptr<Material> create(const std::shared_ptr<Shader>& spShader, const std::shared_ptr<Texture>& spTexture, const std::shared_ptr<RenderState>& spRenderState);

			//! Destructor.
			virtual ~Material();

			//! Bind the material.
			void bind();

			//! Get the material shader.
			std::shared_ptr<Shader> getShader() const { return m_spShader; }
			//! Set the material texture.
			void setTexture(const std::shared_ptr<Texture>& spTexture) { m_spTexture = spTexture; }
			//! Get the material texture.
			std::shared_ptr<Texture> getTexture() const { return m_spTexture; }
			//! Get the material render state.
			std::shared_ptr<RenderState> getRenderState() const { return m_spRenderState; }

		protected:
			//! Protected constructor - must be created by static create().
			Material(const std::shared_ptr<Shader>& spShader, const std::shared_ptr<Texture>& spTexture, const std::shared_ptr<RenderState>& spRenderState);

		private:
			std::shared_ptr<Shader> m_spShader;			//!< Shader used by this material.
			std::shared_ptr<Texture> m_spTexture;			//!< Texture used by this material.
			std::shared_ptr<RenderState> m_spRenderState;	//!< Render state associated with this material.

		};
	}
}