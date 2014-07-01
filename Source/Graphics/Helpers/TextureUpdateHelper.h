#pragma once

#include <boost/shared_ptr.hpp>
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
			static boost::shared_ptr<TextureUpdateHelper> create(const boost::shared_ptr<Renderer> spRenderer);
			
			//! Destructor.
			~TextureUpdateHelper();
			
			//! Render the input texture into the target texture with the specified shader.
			void updateRegion(const boost::shared_ptr<Texture> spInputTexture,
							  const boost::shared_ptr<Texture> spTargetTexture,
							  const boost::shared_ptr<Shader> spShader);

			//! Render the input texture into a sub region of the target texture with the specified shader.
			void updateRegion(const boost::shared_ptr<Texture> spInputTexture,
							  const Vec2& vMinTo, const Vec2& vMaxTo, const boost::shared_ptr<Texture> spTargetTexture,
							  const boost::shared_ptr<Shader> spShader);

			//! Render a sub region of the input texture into a sub region of the target texture with the specified shader.
			void updateRegion(const Vec2& vMinFrom, const Vec2& vMaxFrom, const boost::shared_ptr<Texture> spInputTexture,
							  const Vec2& vMinTo, const Vec2& vMaxTo, const boost::shared_ptr<Texture> spTargetTexture,
							  const boost::shared_ptr<Shader> spShader);

		protected:
			//! Protected constructor - must be created by static create().
			TextureUpdateHelper(const boost::shared_ptr<Renderer> spRenderer);
		
		private:
			//! Initialize.
			void init();

			boost::shared_ptr<Renderer> m_spRenderer;				//!< Renderer used internally for render to texture.
			boost::shared_ptr<FrameBuffer> m_spFrameBuffer;			//!< FrameBuffer used internally to setup texture as render target.
			boost::shared_ptr<StaticGeometry> m_spQuadGeometry;		//!< Quad geometry that is rendered to target texture.
		};
	}
}