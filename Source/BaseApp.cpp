#include "BaseApp.h"

#include <Logging/Log.h>

#include <Graphics/Renderer.h>

using namespace baselib::graphics;

namespace baselib {

	BaseApp::BaseApp()
		: m_dCurrentTime(0.0)
		, m_dPreviousTime(0.0)
		, m_spRenderer(boost::shared_ptr<Renderer>())
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
		LOG_VERBOSE << "BaseApp starting main loop..";
		
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
		// bind shader
		// bind VAO
		// draw - glDraw*
		// unbind VAO
		// unbind shader
	}

	void BaseApp::init()
	{
		LOG_VERBOSE << "BaseApp init";
		m_spRenderer = boost::shared_ptr<Renderer>(new Renderer());
	}

	void BaseApp::destroy()
	{
		LOG_VERBOSE << "BaseApp onDestroy";
	}

}
