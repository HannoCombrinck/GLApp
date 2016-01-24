#include "ResourceLoader.h"

#include <Logging/Log.h>

#include <Graphics/Node.h>

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

	std::shared_ptr<graphics::Node> ResourceLoader::getModel(const std::string& sFilename) 
	{ 
		return null_ptr; 
	}

}
