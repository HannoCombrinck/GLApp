#pragma once

#include <GLFWApp/GLFWApp.h>
#include <memory>

namespace baselib
{
	class ResourceLoader;

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
	/*! @brief Application base manages all baselib components.
	 *
	 */
	class AppBase : public GLFWApp
	{
	public:
		//! Constructor.
		AppBase();
		//! Destructor.
		virtual ~AppBase();

	protected:
		std::shared_ptr<ResourceLoader> GetResourceLoader() const { return m_spResourceLoader; }

	private:
		void onInit(int iWidth, int iHeight);
		void onDestroy();
		void onUpdate(double dDeltaTime);
		void onRender();
		void onWindowResize(int iWidth, int iHeight);

		virtual void onAppInit() {}
		virtual void onAppUpdate(double dDeltaTime) {}

		std::shared_ptr<graphics::Renderer> m_spRenderer;
		std::shared_ptr<graphics::ShaderPipeline> m_spShaderPipeline;
		std::shared_ptr<graphics::StaticGeometry> m_spStaticGeom;
		std::shared_ptr<graphics::Material> m_spMaterial;
		std::shared_ptr<graphics::Node> m_spRootNode;
		std::shared_ptr<graphics::Camera> m_spCamera;
		std::shared_ptr<graphics::VisualCollector> m_spVisualCollector;
		std::shared_ptr<graphics::FrameBuffer> m_spFrameBuffer;
		std::shared_ptr<graphics::RenderJob> m_spRenderJob;

		std::shared_ptr<font::FontLoader> m_spFontLoader;
		std::shared_ptr<font::Font> m_spFont;

		std::shared_ptr<ResourceLoader> m_spResourceLoader;
	};
}