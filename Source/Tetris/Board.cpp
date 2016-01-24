#include "Board.h"

#include <Logging/Log.h>
#include <Core/NullPtr.h>

using namespace baselib;

namespace tetris {
	
	Board::Board()
	{
		LOG_INFO << "Board constructor";
	}

	Board::~Board()
	{
		LOG_INFO << "Board destructor";
	}

}
