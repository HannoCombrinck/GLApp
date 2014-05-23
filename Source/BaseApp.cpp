#include "BaseApp.h"

#include <Logging/Log.h>

namespace baselib {

	BaseApp::BaseApp()
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
		assert(isInitialized() && "App must be initialized before starting.");

		while (isAppRunning())
		{
			processEvents();
			swapBuffers();
		}

		LOG_VERBOSE << "BaseApp main loop stopped";
	}

	void BaseApp::onInit()
	{
		LOG_VERBOSE << "BaseApp onInit";
	}

	void BaseApp::onDestroy()
	{
		LOG_VERBOSE << "BaseApp onDestroy";
	}

}
