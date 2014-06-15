#include "BaseApp.h"

#include <Logging/Log.h>

#include <Graphics/Renderer.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/ShaderPipeline.h>
#include <Graphics/Shader.h>
#include <Graphics/StaticGeometry.h>
#include <Graphics/VertexList.h>

#include <GL/glew.h> //Temp: remove this

using namespace baselib::graphics;

namespace baselib {
	
	BaseApp::BaseApp(int iWidth, int iHeight, bool bFullscreen, int iMajorVersion, int iMinorVersion, const std::string& sWindowTitle)
		: GLFWApp(iWidth, iHeight, bFullscreen, iMajorVersion, iMinorVersion, sWindowTitle)
		, m_dCurrentTime(0.0)
		, m_dPreviousTime(0.0)
		, m_spRenderer(boost::shared_ptr<Renderer>())
		, m_spShaderPipeline(boost::shared_ptr<ShaderPipeline>())
		, m_spShader(boost::shared_ptr<Shader>())
		, m_spStaticGeom(boost::shared_ptr<StaticGeometry>())
	{
		LOG_VERBOSE << "BaseApp constructor";
		init();
	}

	BaseApp::~BaseApp()
	{
		LOG_VERBOSE << "BaseApp destructor";
		destroy();
	}

	void BaseApp::start()
	{
		LOG_VERBOSE << "BaseApp starting main loop";
		
		m_dCurrentTime = GetTime();
		while (isAppRunning())
		{
			m_dPreviousTime = m_dCurrentTime;
			m_dCurrentTime = GetTime();

			processEvents();
			update(m_dCurrentTime - m_dPreviousTime);
			render();
			swapBuffers();
		}

		LOG_VERBOSE << "BaseApp main loop stopped";
	}

	void BaseApp::update(double dDeltaTime)
	{

	}

	void BaseApp::render()
	{
		assert(m_spRenderer);
		m_spRenderer->clear();

		m_spShader->bind();
		m_spStaticGeom->bind();
		m_spRenderer->drawIndexed(m_spStaticGeom->getPrimitiveType(), m_spStaticGeom->getVertexList()->getNumIndices(), 0);
		m_spStaticGeom->unbind();
		m_spShader->unbind();
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
		auto spShaderManager = boost::shared_ptr<ShaderManager>(new ShaderManager());

		auto spVertexShader = spShaderManager->createShaderObject("../Data/Shaders/test.vert");
		auto spFragmentShader = spShaderManager->createShaderObject("../Data/Shaders/test.frag");

		std::vector<boost::shared_ptr<ShaderObject>> aspShaders;
		aspShaders.push_back(spVertexShader);
		aspShaders.push_back(spFragmentShader);

		m_spShaderPipeline = spShaderManager->createShaderPipeline("TestPipeline", aspShaders);
		m_spShader = m_spShaderPipeline->createInstance();


		// Create test VertexList
		auto spVL = boost::shared_ptr<VertexLayout>(new VertexLayout());
		spVL->add(VertexAttribute("position", 0, 3, TYPE_FLOAT, 0));
		spVL->add(VertexAttribute("normal", 1, 3, TYPE_FLOAT, 3*sizeof(float)));
		spVL->add(VertexAttribute("texcoord", 2, 2, TYPE_FLOAT, 6*sizeof(float)));

		auto spVertexList = boost::shared_ptr<VertexList<MyVert>>(new VertexList<MyVert>(spVL));
		spVertexList->addVertex(MyVert(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0, 0.0)));
		spVertexList->addVertex(MyVert(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 0.0)));
		spVertexList->addVertex(MyVert(Vec3(1.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0, 1.0)));
		spVertexList->addIndex(0);
		spVertexList->addIndex(1);
		spVertexList->addIndex(2);

		// Create test static geometry
		m_spStaticGeom = m_spRenderer->createStaticGeometry(spVertexList, Geometry::TRIANGLES);
	}

	void BaseApp::destroy()
	{
		LOG_VERBOSE << "BaseApp onDestroy";
	}

}
