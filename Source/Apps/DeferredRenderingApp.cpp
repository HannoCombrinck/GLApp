#include "DeferredRenderingApp.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/ModelLoader.h>
#include <Graphics/Node.h>
#include <Graphics/Camera.h>
#include <Graphics/CameraController.h>

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

		// Load test model
		auto spModelLoader = ModelLoader::create();
		m_spTestModel = spModelLoader->load("../Data/Models/FbxTest.fbx");

		// Log names of all nodes in model
		m_spTestModel->apply([](const boost::shared_ptr<Spatial>& sp) {
			LOG_INFO << "Model Spatial: " << sp->getName();
		});

		m_spMainCamera = Camera::create();
		m_spCameraController = CameraController::create(m_spMainCamera);
		m_spCameraController->setPosition(Vec3(0.0f, 0.1f, 10.0f));
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

	void DeferredRenderingApp::onKeyPress(int iKey)
	{
		if (iKey == 'M')
			setLockMousePosition(true);
		if (iKey == 'N')
			setLockMousePosition(false);
	}

	void DeferredRenderingApp::onKeyRelease(int iKey)
	{

	}
	
	void DeferredRenderingApp::onMouseMoveRel(int iDX, int iDY)
	{
		if (getLockMousePosition())
		{
			m_spCameraController->rotateX(iDY * 0.25f);
			m_spCameraController->rotateY(iDX * 0.25f);
		}
	}

}
