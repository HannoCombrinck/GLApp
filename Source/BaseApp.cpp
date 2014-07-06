#include "BaseApp.h"

#include <Logging/Log.h>

#include <Graphics/Renderer.h>
#include <Graphics/ShaderObject.h>
#include <Graphics/ShaderPipeline.h>
#include <Graphics/Shader.h>
#include <Graphics/StaticGeometry.h>
#include <Graphics/VertexList.h>
#include <Graphics/ImageLoader.h>
#include <Graphics/Texture.h>
#include <Graphics/Material.h>
#include <Graphics/Node.h>
#include <Graphics/Visual.h>
#include <Graphics/Camera.h>
#include <Graphics/VisualCollector.h>
#include <Graphics/FrameBuffer.h>
#include <Graphics/RenderJob.h>

#include <Font/FontLoader.h>
#include <Font/Font.h>

#include <Helpers/NullPtr.h>

using namespace baselib::graphics;
using namespace baselib::font;

namespace baselib {
	
	BaseApp::BaseApp(int iWidth, int iHeight, bool bFullscreen, int iMajorVersion, int iMinorVersion, const std::string& sWindowTitle)
		: GLFWApp(iWidth, iHeight, bFullscreen, iMajorVersion, iMinorVersion, sWindowTitle)
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
		m_spRenderer = Renderer::create();

		// Create shader objects
		auto spVertexShader = ShaderObject::load("../Data/Shaders/test.vert");
		auto spFragmentShader = ShaderObject::load("../Data/Shaders/test.frag");

		std::vector<boost::shared_ptr<ShaderObject>> aspShaders;
		aspShaders.push_back(spVertexShader);
		aspShaders.push_back(spFragmentShader);

		m_spShaderPipeline = ShaderPipeline::create("TestPipeline", aspShaders);
		auto spShader = m_spShaderPipeline->createInstance();


		// Create test VertexList
		auto spVL = VertexLayout::create();
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
		m_spImageLoader = ImageLoader::create();
		auto spImage = m_spImageLoader->loadImage("../Data/Textures/test.tga");

		// Create test texture
		// TODO: implement texture loader to use ImageLoader
		// m_spTextureLoader = TextureLoader::create();
		// m_spTextureLoader->loadTexture("../Data/Textures/test.tga");
		auto spTexture = Texture::create(spImage);

		// Create test material
		m_spMaterial = Material::create(spShader, spTexture, null_ptr);

		// Create test visual
		auto spVisual = Visual::create(m_spStaticGeom, m_spMaterial);

		// Create test root node
		m_spRootNode = Node::create();
		m_spRootNode->addChild(spVisual);


		// Create test camera
		m_spCamera = Camera::create();
		// Create test visual collector
		m_spVisualCollector = VisualCollector::create();
		// Create test frame buffer
		auto spTargetImage = Image::create(512, 512, 32, 0);
		auto spTargetTexture = Texture::create(spTargetImage);
		std::vector<boost::shared_ptr<Texture>> aTargets;
		aTargets.push_back(spTargetTexture);
		m_spFrameBuffer = FrameBuffer::create(aTargets, null_ptr);
		//m_spFrameBuffer = FrameBuffer::create();

		// Create test render job
		m_spRenderJob = RenderJob::create(m_spRenderer);
		
		// Create test font
		m_spFontLoader = FontLoader::create();
		m_spFont = m_spFontLoader->loadFont("C:/Windows/Fonts/times.ttf", m_spRenderer, Vec2(1024, 1024));
		auto spGlyph = m_spFont->getGlyph('T');
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
