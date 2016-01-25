#include "ResourceLoader.h"

#include <Logging/Log.h>

#include <Graphics/Texture.h>
#include <Graphics/Image.h>
#include <Graphics/ShaderObject.h>

#include <Core/NullPtr.h>

namespace baselib {
	
	ResourceLoader::ResourceLoader()
	{
		LOG_VERBOSE << "ResourceLoader constructor";
	}

	ResourceLoader::~ResourceLoader()
	{
		LOG_VERBOSE << "ResourceLoader destructor";
	}

}
