#include "ImageLoader.h"
#include <Logging/Log.h>

namespace baselib { namespace graphics {

	ImageLoader::ImageLoader()
	{
		LOG_VERBOSE << "ImageLoader constructor";
	}

	ImageLoader::~ImageLoader()
	{
		LOG_VERBOSE << "ImageLoader destructor";
	}

} }