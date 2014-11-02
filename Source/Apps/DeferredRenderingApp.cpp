#include "DeferredRenderingApp.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/ModelLoader.h>
#include <Graphics/Node.h>
#include <Graphics/Camera.h>
#include <Graphics/CameraController.h>
#include <Graphics/Renderer.h>
#include <Graphics/RenderJob.h>

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

		m_spRenderer = Renderer::create();
		m_spMainRenderJob = RenderJob::create(m_spRenderer);
		m_spMainCamera = Camera::create();
		m_spCameraController = CameraController::create(m_spMainCamera);
		m_spCameraController->setPosition(Vec3(0.0f, 0.1f, 10.0f));

		auto spModelLoader = ModelLoader::create();
		auto spTestModel = spModelLoader->load("../Data/Models/FbxTest.fbx");

		// Log names of all nodes in model
		spTestModel->apply([](const boost::shared_ptr<Spatial>& sp) {
			LOG_INFO << "Model Spatial: " << sp->getName();
		});

		m_spRootNode = Node::create();
		m_spRootNode->setName("Root");
		m_spRootNode->addChild(spTestModel);
	}

	void DeferredRenderingApp::onDestroy()
	{
		LOG_VERBOSE << "DeferredRenderingApp onDestroy";
	}

	void DeferredRenderingApp::onUpdate(double dDeltaTime)
	{
		m_spRootNode->update(Mat4());
	}

	void DeferredRenderingApp::onRender()
	{
	}

	void DeferredRenderingApp::onWindowResize(int iWidth, int iHeight)
	{
	}

	void DeferredRenderingApp::onKeyPress(int iKey)
	{
		if (iKey == 'W')
			m_spCameraController->setMovingForward(true);
		if (iKey == 'S')
			m_spCameraController->setMovingBack(true);
		if (iKey == 'A')
			m_spCameraController->setMovingLeft(true);
		if (iKey == 'D')
			m_spCameraController->setMovingRight(true);

		if (iKey == 'M')
			setLockMousePosition(true);
		if (iKey == 'N')
			setLockMousePosition(false);
	}

	void DeferredRenderingApp::onKeyRelease(int iKey)
	{
		if (iKey == 'W')
			m_spCameraController->setMovingForward(false);
		if (iKey == 'S')
			m_spCameraController->setMovingBack(false);
		if (iKey == 'A')
			m_spCameraController->setMovingLeft(false);
		if (iKey == 'D')
			m_spCameraController->setMovingRight(false);
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
