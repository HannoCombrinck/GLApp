#pragma once

#include <memory>
#include <Math/Math.h>

namespace baselib 
{
	namespace graphics
	{
		class Renderer;
		class RenderJob;
		class Texture;
		class VisualCollector;
		class FrameBuffer;
		class Shader;
		class StaticGeometry;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! brief TextureUpdateHelper
		 *
		 */
		class TextureUpdateHelper
		{
		public:
			//! Creates a TextureUpdateHelper.
			static std::shared_ptr<TextureUpdateHelper> create(const std::shared_ptr<Renderer> spRenderer);
			
			//! Destructor.
			~TextureUpdateHelper();
			
			//! Render the input texture into the target texture with the specified shader.
			void updateRegion(const std::shared_ptr<Texture> spInputTexture,
							  const std::shared_ptr<Texture> spTargetTexture,
							  const std::shared_ptr<Shader> spShader);

			//! Render the input texture into a sub region of the target texture with the specified shader.
			void updateRegion(const std::shared_ptr<Texture> spInputTexture,
							  const Vec2& vMinTo, const Vec2& vMaxTo, const std::shared_ptr<Texture> spTargetTexture,
							  const std::shared_ptr<Shader> spShader);

			//! Render a sub region of the input texture into a sub region of the target texture with the specified shader.
			void updateRegion(const Vec2& vMinFrom, const Vec2& vMaxFrom, const std::shared_ptr<Texture> spInputTexture,
							  const Vec2& vMinTo, const Vec2& vMaxTo, const std::shared_ptr<Texture> spTargetTexture,
							  const std::shared_ptr<Shader> spShader);

		protected:
			//! Protected constructor - must be created by static create().
			TextureUpdateHelper(const std::shared_ptr<Renderer> spRenderer);
		
		private:
			//! Initialize.
			void init();

			std::shared_ptr<Renderer> m_spRenderer;				//!< Renderer used internally for render to texture.
			std::shared_ptr<FrameBuffer> m_spFrameBuffer;			//!< FrameBuffer used internally to setup texture as render target.
			std::shared_ptr<StaticGeometry> m_spQuadGeometry;		//!< Quad geometry that is rendered to target texture.
		};
	}
}