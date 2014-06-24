#include "BaseApp.h"

#include <Logging/Log.h>

#include <Graphics/Renderer.h>
#include <Graphics/ShaderFactory.h>
#include <Graphics/ShaderPipeline.h>
#include <Graphics/Shader.h>
#include <Graphics/StaticGeometry.h>
#include <Graphics/VertexList.h>
#include <Graphics/ImageLoader.h>
#include <Graphics/TextureFactory.h>
#include <Graphics/Material.h>
#include <Graphics/Node.h>
#include <Graphics/Visual.h>
#include <Graphics/Camera.h>
#include <Graphics/VisualCollector.h>
#include <Graphics/FrameBuffer.h>
#include <Graphics/RenderJob.h>

#include <Helpers/NullPtr.h>

#include <GL/glew.h> //Temp: remove this

using namespace baselib::graphics;

namespace baselib {
	
	BaseApp::BaseApp(int iWidth, int iHeight, bool bFullscreen, int iMajorVersion, int iMinorVersion, const std::string& sWindowTitle)
		: GLFWApp(iWidth, iHeight, bFullscreen, iMajorVersion, iMinorVersion, sWindowTitle)
		, m_spRenderer(null_ptr)
		, m_spShaderPipeline(null_ptr)
		, m_spStaticGeom(null_ptr)
		, m_spImageLoader(null_ptr)
		, m_spTextureFactory(null_ptr)
		, m_spMaterial(null_ptr)
		, m_spRootNode(null_ptr)
		, m_spCamera(null_ptr)
		, m_spVisualCollector(null_ptr)
		, m_spFrameBuffer(null_ptr)
		, m_spRenderJob(null_ptr)
	{
		LOG_VERBOSE << "BaseApp constructor";
		init();
	}

	BaseApp::~BaseApp()
	{
		LOG_VERBOSE << "BaseApp destructor";
		destroy();
	}

	void BaseApp::onUpdate(double dDeltaTime)
	{
		m_spRootNode->update(Mat4());
	}

	void BaseApp::onRender()
	{
		assert(m_spRenderer);
		m_spRenderer->clear();
		m_spRenderJob->execute(m_spRootNode, m_spVisualCollector, m_spFrameBuffer, m_spCamera);
	}

	// Test vertex
	struct MyVert
	{
		MyVert(Vec3 vP, Vec3 vN, Vec2 _vUV)
			: vPos(vP)
			, vNormal(vN)
			, vUV(_vUV) {}

		Vec3 vPos;
		Vec3 vNormal;
		Vec2 vUV;
	};

	void BaseApp::init()
	{
		LOG_VERBOSE << "BaseApp init";

		// Create test renderer
		m_spRenderer = boost::shared_ptr<Renderer>(new Renderer());

		// Create test shader manager and test shader
		auto spShaderFactory = boost::shared_ptr<ShaderFactory>(new ShaderFactory());

		auto spVertexShader = spShaderFactory->createShaderObject("../Data/Shaders/test.vert");
		auto spFragmentShader = spShaderFactory->createShaderObject("../Data/Shaders/test.frag");

		std::vector<boost::shared_ptr<ShaderObject>> aspShaders;
		aspShaders.push_back(spVertexShader);
		aspShaders.push_back(spFragmentShader);

		m_spShaderPipeline = spShaderFactory->createShaderPipeline("TestPipeline", aspShaders);
		auto spShader = m_spShaderPipeline->createInstance();


		// Create test VertexList
		auto spVL = boost::shared_ptr<VertexLayout>(new VertexLayout());
		spVL->add(VertexAttribute("position", 0, 3, TYPE_FLOAT, 0));
		spVL->add(VertexAttribute("normal", 1, 3, TYPE_FLOAT, 3*sizeof(float)));
		spVL->add(VertexAttribute("texcoord", 2, 2, TYPE_FLOAT, 6*sizeof(float), true));

		auto spVertexList = boost::shared_ptr<VertexList<MyVert>>(new VertexList<MyVert>(spVL));
		spVertexList->addVertex(MyVert(Vec3(-0.5f, -0.5f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0, 0.0)));
		spVertexList->addVertex(MyVert(Vec3(0.5f, -0.5f, 0.0f),  Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 0.0)));
		spVertexList->addVertex(MyVert(Vec3(0.5f, 0.5f, 0.0f),   Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 1.0)));
		spVertexList->addVertex(MyVert(Vec3(-0.5f, 0.5f, 0.0f),  Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0, 1.0)));
		spVertexList->addIndex(0);
		spVertexList->addIndex(1);
		spVertexList->addIndex(2);
		spVertexList->addIndex(0);
		spVertexList->addIndex(2);
		spVertexList->addIndex(3);

		// Create test static geometry
		m_spStaticGeom = m_spRenderer->createStaticGeometry(spVertexList, Geometry::TRIANGLES);

		// Load test image 
		m_spImageLoader = boost::shared_ptr<ImageLoader>(new ImageLoader());
		auto spImage = m_spImageLoader->loadImage("../Data/Textures/test.tga");

		// Create test texture
		m_spTextureFactory = boost::shared_ptr<TextureFactory>(new TextureFactory());
		auto spTexture = m_spTextureFactory->createTexture(spImage);

		// Create test material
		m_spMaterial = boost::shared_ptr<Material>(new Material(spShader, spTexture, null_ptr));

		// Create test visual
		auto spVisual = boost::shared_ptr<Visual>(new Visual(m_spStaticGeom, m_spMaterial));

		// Create test root node
		m_spRootNode = boost::shared_ptr<Node>(new Node());
		m_spRootNode->addChild(spVisual);


		// Create test camera
		m_spCamera = boost::shared_ptr<Camera>(new Camera());
		// Create test visual collector
		m_spVisualCollector = boost::shared_ptr<VisualCollector>(new VisualCollector());
		// Create test frame buffer
		m_spFrameBuffer = boost::shared_ptr<FrameBuffer>(new FrameBuffer());

		// Create test render job
		m_spRenderJob = boost::shared_ptr<RenderJob>(new RenderJob(m_spRenderer));
	}

	void BaseApp::destroy()
	{
		LOG_VERBOSE << "BaseApp onDestroy";
	}

	void BaseApp::onWindowResize(int iWidth, int iHeight)
	{
		if (m_spRenderer)
			m_spRenderer->setViewportSize(Vec4(0, 0, iWidth, iHeight));
	}

}
