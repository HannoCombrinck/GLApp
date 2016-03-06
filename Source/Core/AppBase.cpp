#include "AppBase.h"

#include <Logging/Log.h>

#include <Core/ResourceLoader.h>

#include <Graphics/Renderer.h>

#include <Core/NullPtr.h>

using namespace baselib::graphics;

namespace baselib {
	
	AppBase::AppBase()
	{
		LOG_VERBOSE << "AppBase constructor";
	}

	AppBase::~AppBase()
	{
		LOG_VERBOSE << "AppBase destructor";
	}

	void AppBase::onInit(int iWidth, int iHeight)
	{
		LOG_VERBOSE << "AppBase init";

		m_spResourceLoader = ResourceLoader::create();

		onAppInit();
	}

	void AppBase::onDestroy()
	{
		LOG_VERBOSE << "AppBase onDestroy";
		onAppDestroy();
	}

	void AppBase::onUpdate(double dDeltaTime)
	{
		onAppUpdate(dDeltaTime);
	}

	void AppBase::onRender()
	{
		
	}

	void AppBase::onWindowResize(int iWidth, int iHeight)
	{
		LOG_INFO << "Resizing window to: " << iWidth << "x" << iHeight;
	}

}
