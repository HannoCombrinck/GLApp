#include "Material.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Material::Material()
	{
		LOG_VERBOSE << "Material constructor";
	}

	Material::~Material()
	{
		LOG_VERBOSE << "Material destructor";
	}

} }