#include "Visual.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Visual::Visual()
		: m_spMaterial(boost::shared_ptr<Material>())
		, m_spGeometry(boost::shared_ptr<Geometry>())
	{
		LOG_VERBOSE << "Visual constructor";
	}

	Visual::~Visual()
	{
		LOG_VERBOSE << "Visual destructor";
	}

} }