#include "Visual.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Visual::Visual(const boost::shared_ptr<Geometry>& spGeometry, const boost::shared_ptr<Material>& spMaterial)
		: m_spGeometry(spGeometry)
		, m_spMaterial(spMaterial)
	{
		LOG_VERBOSE << "Visual constructor";
	}

	Visual::~Visual()
	{
		LOG_VERBOSE << "Visual destructor";
	}

	void Visual::onUpdate(const Mat4& mParent)
	{
		// TODO
	}

} }