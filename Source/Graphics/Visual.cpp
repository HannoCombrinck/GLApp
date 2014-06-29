#include "Visual.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<Visual> Visual::create(const boost::shared_ptr<Geometry>& spGeometry, const boost::shared_ptr<Material>& spMaterial)
	{
		return boost::shared_ptr<Visual>(new Visual(spGeometry, spMaterial));
	}

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