#pragma once

#include <GLFWApp/GLFWApp.h>

namespace baselib
{
	namespace graphics
	{
		class Renderer;
		class RenderJob;
		class Node;
		class VisualCollector;
		class Camera;
		class CameraController;
	}
}

namespace baselib
{
	//! @brief Basic deferred rendering test application
	class DeferredRenderingApp : public GLFWApp
	{
	public:
		DeferredRenderingApp();
		virtual ~DeferredRenderingApp();

	private:
		void onInit(int iWidth, int iHeight);
		void onDestroy();
		void onUpdate(double dDeltaTime);
		void onRender();
		void onWindowResize(int iWidth, int iHeight);

		void onKeyPress(int iKey);
		void onKeyRelease(int iKey);
		void onMouseMoveRel(int iDX, int iDY);

		boost::shared_ptr<graphics::Renderer> m_spRenderer;
		boost::shared_ptr<graphics::RenderJob> m_spMainRenderJob;
		boost::shared_ptr<graphics::Node> m_spRootNode;
		boost::shared_ptr<graphics::VisualCollector> m_spVisualCollector;
		boost::shared_ptr<graphics::Camera> m_spMainCamera;
		boost::shared_ptr<graphics::CameraController> m_spCameraController;
	};
}