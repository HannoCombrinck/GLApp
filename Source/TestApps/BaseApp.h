#pragma once

#include <GLFWApp/GLFWApp.h>
#include <memory>

namespace baselib
{
	namespace graphics
	{
		class Renderer;
		class ShaderPipeline;
		class StaticGeometry;
		class Material;
		class Node;
		class Camera;
		class VisualCollector;
		class FrameBuffer;
		class RenderJob;
	}

	namespace font
	{
		class FontLoader;
		class Font;
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
		BaseApp();
		//! Destructor.
		virtual ~BaseApp();

	private:
		void onInit(int iWidth, int iHeight);
		void onDestroy();
		void onUpdate(double dDeltaTime);
		void onRender();
		void onWindowResize(int iWidth, int iHeight);

		std::shared_ptr<graphics::Renderer> m_spRenderer; //!< Main renderer
		std::shared_ptr<graphics::ShaderPipeline> m_spShaderPipeline; //!< Test shader pipeline
		std::shared_ptr<graphics::StaticGeometry> m_spStaticGeom; //!< Test geometry
		std::shared_ptr<graphics::Material> m_spMaterial; //!< Test material
		std::shared_ptr<graphics::Node> m_spRootNode; //!< Test node
		std::shared_ptr<graphics::Camera> m_spCamera; //!< Test camera
		std::shared_ptr<graphics::VisualCollector> m_spVisualCollector; //!< Test visual collector
		std::shared_ptr<graphics::FrameBuffer> m_spFrameBuffer; //!< Test frame buffer
		std::shared_ptr<graphics::RenderJob> m_spRenderJob; //!< Test render job

		std::shared_ptr<font::FontLoader> m_spFontLoader; //!< Test font loader
		std::shared_ptr<font::Font> m_spFont; //!< Test font
	};
}