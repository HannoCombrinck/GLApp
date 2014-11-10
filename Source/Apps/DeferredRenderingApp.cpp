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
#include <Graphics/Geometry.h>
#include <Graphics/VertexList.h>
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
		: m_bAnimateLights(false)
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
			std::vector<boost::shared_ptr<ShaderObject>> aspShaders;
			aspShaders.push_back(ShaderObject::load(sVertexShader));
			aspShaders.push_back(ShaderObject::load(sFragmentShader));
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
		m_spColourTarget1 = Texture::createRenderTarget( Image::create(iWidth, iHeight, 128, 0) );
		m_spColourTarget2 = Texture::createRenderTarget( Image::create(iWidth, iHeight, 128, 0) );
		m_spColourTarget3 = Texture::createRenderTarget( Image::create(iWidth, iHeight, 128, 0) );
		m_spColourTarget4 = Texture::createRenderTarget( Image::create(iWidth, iHeight, 128, 0) );
		m_spDepthTarget = Texture::createRenderTarget( Image::create(iWidth, iHeight, 24, 0) );

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
		for (int i = 0; i < 300;  ++i)
		{
			auto fRandX = (rand()/float(RAND_MAX) * 2575.0f) - 1386.0f;
			auto fRandY = (rand()/float(RAND_MAX) * 800.0f);
			auto fRandZ = (rand()/float(RAND_MAX) * 2575.0f) - 1386.0f;
			//auto fRandZ = (rand()/float(RAND_MAX) * 1090.0f) - 560.0f;
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

		if (m_bAnimateLights)
			m_spLightScene->modifyLocalTransform() = glm::rotate(m_spLightScene->getLocalTransform(), toRadians(1.0f), Vec3(0.0, 1.0, 0.0));

		m_spMainScene->update(Mat4());
		m_spLightScene->update(Mat4());
	}

	void DeferredRenderingApp::onRender()
	{
		// Setup GBuffer as render target
		m_spGBuffer->bind();
		m_spRenderer->setViewportSize(Vec4(0, 0, m_spGBuffer->getWidth(), m_spGBuffer->getHeight()));
		m_spRenderer->setRenderState(Renderer::STATE_CULL_MODE, Renderer::CULL_BACK);
		m_spRenderer->setRenderState(Renderer::STATE_BLEND, Renderer::FALSE);
		m_spRenderer->setRenderState(Renderer::STATE_DEPTH_TEST, Renderer::TRUE);
		m_spRenderer->setRenderState(Renderer::STATE_DEPTH_WRITE, Renderer::TRUE);
		m_spRenderer->clear();


		// Bind GBuffer shader and upload common uniform data
		m_spGBufferShader->bind();
		m_spGBufferShader->setUniform("mProjection", m_spMainCamera->getProjectionMatrix());
		m_spGBufferShader->setUniform("mView", m_spMainCamera->getViewMatrix());
		m_spGBufferShader->setUniform("sDiffuse", 0);

		// Render all visuals in main scene
		m_spVisualCollector->clear();
		m_spVisualCollector->collect(m_spMainScene);
		auto& spGBufferShader = m_spGBufferShader;
		boost::for_each(m_spVisualCollector->getVisuals(), [this, &spGBufferShader](const Visual* pVisual) {
			spGBufferShader->setUniform("mWorld", pVisual->getWorldTransform());
			if (auto spTexture = pVisual->getMaterial()->getTexture())
				spTexture->bind();
			auto spGeometry = pVisual->getGeometry();
			spGeometry->bind();
			m_spRenderer->drawIndexed(spGeometry->getPrimitiveType(), spGeometry->getVertexList()->getNumIndices(), 0);
		});

		// Setup back buffer as render target
		auto spBackBuffer = m_spRenderer->getBackBuffer();
		spBackBuffer->bind();
		m_spRenderer->setViewportSize(Vec4(0, 0, spBackBuffer->getWidth(), spBackBuffer->getHeight()));
		m_spRenderer->setRenderState(Renderer::STATE_CULL_MODE, Renderer::CULL_FRONT);
		m_spRenderer->setRenderState(Renderer::STATE_BLEND, Renderer::TRUE);
		m_spRenderer->setRenderState(Renderer::STATE_BLEND_SRC, Renderer::ONE);
		m_spRenderer->setRenderState(Renderer::STATE_BLEND_DST, Renderer::ONE);
		m_spRenderer->setRenderState(Renderer::STATE_DEPTH_TEST, Renderer::FALSE);
		m_spRenderer->setRenderState(Renderer::STATE_DEPTH_WRITE, Renderer::FALSE);
		m_spRenderer->clear();

		// Bind light volume shader and upload common uniform data
		m_spLightVolumeShader->bind();
		m_spLightVolumeShader->setUniform("mProjection", m_spMainCamera->getProjectionMatrix());
		m_spLightVolumeShader->setUniform("mView", m_spMainCamera->getViewMatrix());
		m_spLightVolumeShader->setUniform("sWorldPos", 0);
		m_spLightVolumeShader->setUniform("sDiffuse", 1);
		m_spLightVolumeShader->setUniform("sNormal", 2);

		// Bind GBuffer target textures
		m_spColourTarget1->bind(0);
		m_spColourTarget2->bind(1);
		m_spColourTarget3->bind(2);

		// Render all light volume visuals in light scene
		m_spVisualCollector->clear();
		m_spVisualCollector->collect(m_spLightScene);
		auto& spLightVolumeShader = m_spLightVolumeShader;
		boost::for_each(m_spVisualCollector->getVisuals(), [this, &spLightVolumeShader](const Visual* pVisual) {
			spLightVolumeShader->setUniform("mWorld", pVisual->getWorldTransform());
			spLightVolumeShader->setUniform("fLightSize", 200.0f);
			auto vPos = Vec3(pVisual->getWorldTransform()[3]);
			spLightVolumeShader->setUniform("vLightPosition", vPos);
			auto spGeometry = pVisual->getGeometry();
			spGeometry->bind();
			m_spRenderer->drawIndexed(spGeometry->getPrimitiveType(), spGeometry->getVertexList()->getNumIndices(), 0);
		});
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

		if (iKey == 'F')
			m_bAnimateLights = !m_bAnimateLights;
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
