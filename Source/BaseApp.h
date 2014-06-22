#pragma once

#include <GLFWApp/GLFWApp.h>
#include <boost/shared_ptr.hpp>

namespace baselib
{
	namespace graphics
	{
		class Renderer;
		class ShaderPipeline;
		class StaticGeometry;
		class ImageLoader;
		class TextureFactory;
		class Material;
		class Node;
		class Camera;
		class VisualCollector;
		class FrameBuffer;
		class RenderJob;
	}
}

namespace baselib
{
	/*! @brief Test app
	 *
	 */
	class BaseApp : public GLFWApp
	{
	public:
		//! Constructor.
		BaseApp(int iWidth, int iHeight, bool bFullscreen, int iMajorVersion, int iMinorVersion, const std::string& sWindowTitle);
		//! Destructor.
		virtual ~BaseApp();

	private:
		//! Main update function. Called from main loop.
		virtual void onUpdate(double dDeltaTime);
		//! Main render function. Called from main loop.
		virtual void onRender();

		//! Initialization happens here.
		void init();
		//! Cleanup happens here.
		void destroy();

		virtual void onWindowResize(int iWidth, int iHeight);

		boost::shared_ptr<graphics::Renderer> m_spRenderer; //!< Main renderer
		boost::shared_ptr<graphics::ShaderPipeline> m_spShaderPipeline; //!< Test shader pipeline
		boost::shared_ptr<graphics::StaticGeometry> m_spStaticGeom; //!< Test geometry
		boost::shared_ptr<graphics::ImageLoader> m_spImageLoader; //!< Test image loader
		boost::shared_ptr<graphics::TextureFactory> m_spTextureFactory; //!< Test texture factory
		boost::shared_ptr<graphics::Material> m_spMaterial; //!< Test material
		boost::shared_ptr<graphics::Node> m_spRootNode; //!< Test node
		boost::shared_ptr<graphics::Camera> m_spCamera; //!< Test camera
		boost::shared_ptr<graphics::VisualCollector> m_spVisualCollector; //!< Test visual collector
		boost::shared_ptr<graphics::FrameBuffer> m_spFrameBuffer; //!< Test frame buffer
		boost::shared_ptr<graphics::RenderJob> m_spRenderJob; //!< Test render job
	};
}