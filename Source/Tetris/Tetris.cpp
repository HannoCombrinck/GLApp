#include "Tetris.h"

#include <Logging/Log.h>

#include <Core/NullPtr.h>

using namespace baselib;

namespace tetris {
	
	Tetris::Tetris()
	{
		LOG_INFO << "Tetris constructor";
	}

	Tetris::~Tetris()
	{
		LOG_INFO << "Tetris destructor";
	}

	void Tetris::onAppInit()
	{
		LOG_INFO << "Tetris init";
		// Load assets here
	}

	void Tetris::onAppUpdate(double dDeltaTime)
	{
		auto dt = dDeltaTime;
	}

}
