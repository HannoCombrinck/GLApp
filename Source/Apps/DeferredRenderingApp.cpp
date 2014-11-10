#include "DeferredRenderingApp.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/ModelLoader.h>
#include <Graphics/Node.h>
#include <Graphics/Camera.h>
#include <Graphics/CameraController.h>
#include <Graphics/Renderer.h>
#include <Graphics/RenderJob.h>
#include <Graphics/VisualCollector.h>
#include <Graphics/Visual.h>
#include <Graphics/Spatial.h>
#include <Graphics/ShaderPipeline.h>
#include <Graphics/ShaderObject.h>
#include <Graphics/Shader.h>
#include <Graphics/FrameBuffer.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Graphics/Image.h>

#include <Math/MathHelpers.h>

#include <boost/shared_ptr.hpp>

#include <boost/range/algorithm/for_each.hpp>

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

	namespace
	{
		boost::shared_ptr<Shader> createSimpleShader(const std::string& sPipelineName, const std::string& sVertexShader, const std::string& sFragmentShader)
		{
			auto spVertexShader = ShaderObject::load(sVertexShader);
			auto spFragmentShader = ShaderObject::load(sFragmentShader);
			std::vector<boost::shared_ptr<ShaderObject>> aspShaders;
			aspShaders.push_back(spVertexShader);
			aspShaders.push_back(spFragmentShader);
			auto spShaderPipeline = ShaderPipeline::create(sPipelineName, aspShaders);
			return spShaderPipeline->createInstance();
		}
	}

	void DeferredRenderingApp::onInit(int iWidth, int iHeight)
	{
		LOG_VERBOSE << "DeferredRenderingApp init";

		m_spRenderer = Renderer::create(iWidth, iHeight);
		m_spMainRenderJob = RenderJob::create(m_spRenderer);
		m_spVisualCollector = VisualCollector::create();
		m_spMainCamera = Camera::create();
		m_spMainCamera->setAspectRatio(float(iWidth)/float(iHeight));
		m_spCameraController = CameraController::create(m_spMainCamera);
		m_spCameraController->setPosition(Vec3(0.0f, 0.1f, 10.0f));

		// Create GBuffer
		auto spTargetImage1 = Image::create(iWidth, iHeight, 128, 0);
		auto spTargetImage2 = Image::create(iWidth, iHeight, 128, 0);
		auto spTargetImage3 = Image::create(iWidth, iHeight, 128, 0);
		auto spTargetImage4 = Image::create(iWidth, iHeight, 128, 0);
		auto spDepthTargetImage = Image::create(iWidth, iHeight, 24, 0);

		m_spColourTarget1 = Texture::createRenderTarget(spTargetImage1);
		m_spColourTarget2 = Texture::createRenderTarget(spTargetImage2);
		m_spColourTarget3 = Texture::createRenderTarget(spTargetImage3);
		m_spColourTarget4 = Texture::createRenderTarget(spTargetImage4);
		m_spDepthTarget = Texture::createRenderTarget(spDepthTargetImage);

		std::vector<boost::shared_ptr<Texture>> aTargets;
		aTargets.push_back(m_spColourTarget1);
		aTargets.push_back(m_spColourTarget2);
		aTargets.push_back(m_spColourTarget3);
		aTargets.push_back(m_spColourTarget4);

		m_spGBuffer = FrameBuffer::create(aTargets, m_spDepthTarget);
		
		// Create GBuffer shader
		m_spGBufferShader = createSimpleShader("GBufferPipeline", "../Data/Shaders/GBuffer.vert", "../Data/Shaders/GBuffer.frag");

		// Create light volume shader
		m_spLightVolumeShader = createSimpleShader("LightVolumePipeline", "../Data/Shaders/LightVolume.vert", "../Data/Shaders/LightVolume.frag");

		// Create model loader
		auto spModelLoader = ModelLoader::create();
		// Load test scene
		auto spTestModel = spModelLoader->load("../Data/Models/sponza/sponza.fbx");

		// Load scene with sphere
		auto spUnitSphere = spModelLoader->load("../Data/Models/UnitSphere.fbx");
		// Get sphere Visual from scene
		boost::shared_ptr<Visual> spSphereVisual = null_ptr;
		spUnitSphere->apply([&spSphereVisual] (const boost::shared_ptr<Spatial>& sp) {
			if (auto spVisual = boost::dynamic_pointer_cast<Visual>(sp))
				spSphereVisual = spVisual;
		});
		spSphereVisual->getMaterial()->setTexture(m_spColourTarget2);

		// Populate light scene
		m_spLightScene = Node::create();
		m_spLightScene->setName("LightScene");
		for (int i = 0; i < 1000;  ++i)
		{
			auto fRandX = (rand()/float(RAND_MAX) * 2575.0f) - 1386.0f;
			auto fRandY = (rand()/float(RAND_MAX) * 700.0f) + 100.0f;
			auto fRandZ = (rand()/float(RAND_MAX) * 1090.0f) - 560.0f;
			auto vPos = Vec3(fRandX, fRandY, fRandZ);
			auto spSphereCopy = spSphereVisual->shallowCopy();
			spSphereCopy->modifyLocalTransform() = glm::translate(spSphereCopy->getLocalTransform(), vPos);
			m_spLightScene->addChild(spSphereCopy);
		}

		m_spMainScene = Node::create();
		m_spMainScene->setName("SceneRoot");
		m_spMainScene->addChild(spTestModel);
	}

	void DeferredRenderingApp::onDestroy()
	{
		LOG_VERBOSE << "DeferredRenderingApp onDestroy";
	}

	void DeferredRenderingApp::onUpdate(double dDeltaTime)
	{
		m_spCameraController->update(dDeltaTime);

		//m_spLightScene->modifyLocalTransform() = glm::rotate(m_spLightScene->getLocalTransform(), toRadians(1.0f), Vec3(0.0, 1.0, 0.0));

		m_spMainScene->update(Mat4());
		m_spLightScene->update(Mat4());
	}

	void DeferredRenderingApp::onRender()
	{
		// Collect visual from main scene and render them to back buffer
		m_spVisualCollector->clear();
		m_spVisualCollector->collect(m_spMainScene);
		m_spMainRenderJob->execute(m_spVisualCollector->getVisuals(), m_spGBuffer, m_spMainCamera, m_spGBufferShader);

		// Collect light volume visuals from light scene and render to back buffer
		m_spVisualCollector->clear();
		m_spVisualCollector->collect(m_spLightScene);
		m_spMainRenderJob->execute(m_spVisualCollector->getVisuals(), m_spRenderer->getBackBuffer(), m_spMainCamera, m_spLightVolumeShader);
	}

	void DeferredRenderingApp::onWindowResize(int iWidth, int iHeight)
	{
		if (m_spRenderer)
			m_spRenderer->resizeBackBuffer(iWidth, iHeight);
		if (m_spMainCamera)
			m_spMainCamera->setAspectRatio(float(iWidth)/float(iHeight));

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

		if (iKey == 'Q')
			setLockMousePosition(true);
		if (iKey == 'E')
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
			m_spCameraController->rotateX(iDY * -0.25f);
			m_spCameraController->rotateY(iDX * -0.25f);
		}
	}

}
