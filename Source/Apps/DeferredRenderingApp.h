#pragma once

#include <GLFWApp/GLFWApp.h>
#include <boost/shared_ptr.hpp>

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
	};
}