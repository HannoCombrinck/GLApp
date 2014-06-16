#include "TextureFactory.h"

#include <GL/glew.h>
#include <Helpers/NullPtr.h>
#include <Logging/Log.h>

namespace baselib { namespace graphics {

	TextureFactory::TextureFactory()
	{
		LOG_VERBOSE << "TextureFactory constructor";
	}

	TextureFactory::~TextureFactory()
	{
		LOG_VERBOSE << "TextureFactory destructor";
	}

	boost::shared_ptr<Texture> TextureFactory::createTexture(const fs::path& fsPath)
	{
		LOG_INFO << "TODO";
		assert(false);
		return null_ptr;
	}

} }