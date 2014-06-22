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

		//! Start and run the main update loop in this thread. This function returns when the app is stopped.
		void start();

	private:
		//! Main update function. Called from main loop.
		void update(double dDeltaTime);
		//! Main render function. Called from main loop.
		void render();

		//! Initialization happens here.
		void init();
		//! Cleanup happens here.
		void destroy();

		virtual void onWindowResize(int iWidth, int iHeight);

		double m_dCurrentTime;  //!< Current time elapsed since application started.
		double m_dPreviousTime; //!< Time elapsed up to previous update cycle. So time elapsed since previous update = m_dCurrentTime - m_dPreviousTime.

		boost::shared_ptr<graphics::Renderer> m_spRenderer; //!< Main renderer
		boost::shared_ptr<graphics::ShaderPipeline> m_spShaderPipeline; //!< Test shader pipeline
		boost::shared_ptr<graphics::StaticGeometry> m_spStaticGeom; //!< Test geometry
		boost::shared_ptr<graphics::ImageLoader> m_spImageLoader; //!< Test image loader
		boost::shared_ptr<graphics::TextureFactory> m_spTextureFactory; //!< Test texture factory
		boost::shared_ptr<graphics::Material> m_spMaterial; //!< Test material
		boost::shared_ptr<graphics::Node> m_spRootNode; //!< Test node
	};
}