#include "DeferredRenderingApp.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/ModelLoader.h>
#include <Graphics/Node.h>

#include <boost/shared_ptr.hpp>

using namespace baselib::graphics;

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

		auto spModelLoader = ModelLoader::create();
		m_spTestModel = spModelLoader->load("../Data/Models/FbxTest.fbx");
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
