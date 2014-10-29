#pragma once

#include <GLFWApp/GLFWApp.h>

namespace baselib
{
	namespace graphics
	{
		class Node;
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
		void onInit();
		void onDestroy();
		void onUpdate(double dDeltaTime);
		void onRender();
		void onWindowResize(int iWidth, int iHeight);

		boost::shared_ptr<graphics::Node> m_spTestModel;
	};
}