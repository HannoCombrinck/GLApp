#include "TextureManager.h"

#include <GL/glew.h>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <Logging/Log.h>

namespace baselib { namespace graphics {

	TextureManager::TextureManager()
	{
		LOG_VERBOSE << "TextureManager constructor";
	}

	TextureManager::~TextureManager()
	{
		LOG_VERBOSE << "TextureManager destructor";
	}

	boost::shared_ptr<Texture> TextureManager::createTexture(const fs::path& fsPath)
	{
		LOG_INFO << "TODO";
		assert(false);
		return boost::shared_ptr<Texture>();
	}

} }