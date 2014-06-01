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
	}

	BaseApp::~BaseApp()
	{
		LOG_VERBOSE << "BaseApp destructor";
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

	}

	void BaseApp::onInit()
	{
		LOG_VERBOSE << "BaseApp onInit";

		m_spRenderer = boost::shared_ptr<Renderer>(new Renderer());
	}

	void BaseApp::onDestroy()
	{
		LOG_VERBOSE << "BaseApp onDestroy";
	}

}
