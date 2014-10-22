#include "DeferredRenderingApp.h"

#include <Logging/Log.h>

#include <Helpers/NullPtr.h>

namespace baselib {
	
	DeferredRenderingApp::DeferredRenderingApp()
	{
		LOG_VERBOSE << "DeferredRenderingApp constructor";
	}

	DeferredRenderingApp::~DeferredRenderingApp()
	{
		LOG_VERBOSE << "DeferredRenderingApp destructor";
	}

	void DeferredRenderingApp::onInit()
	{
		LOG_VERBOSE << "DeferredRenderingApp init";
	}

	void DeferredRenderingApp::onDestroy()
	{
		LOG_VERBOSE << "DeferredRenderingApp onDestroy";
	}

	void DeferredRenderingApp::onUpdate(double dDeltaTime)
	{
	}

	void DeferredRenderingApp::onRender()
	{
	}

	void DeferredRenderingApp::onWindowResize(int iWidth, int iHeight)
	{
	}

}
