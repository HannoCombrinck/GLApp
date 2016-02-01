#include "Tetris.h"

#include <Logging/Log.h>

#include <Core/ResourceLoader.h>
#include <Core/NullPtr.h>
#include <boost/filesystem.hpp>

#include <Graphics/TextureGLI.h>

namespace fs = boost::filesystem;

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

		// Test dds texture load
		auto spTex = graphics::TextureGLI::load("../Data/Textures/test.dds");
	}

	void Tetris::onAppUpdate(double dDeltaTime)
	{
		auto dt = dDeltaTime;
	}

}
