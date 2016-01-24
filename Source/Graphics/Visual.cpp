#include "Visual.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	std::shared_ptr<Visual> Visual::create(const std::shared_ptr<Geometry>& spGeometry, const std::shared_ptr<Material>& spMaterial)
	{
		return std::shared_ptr<Visual>(new Visual(spGeometry, spMaterial));
	}

	std::shared_ptr<Visual> Visual::shallowCopy()
	{
		auto spVisual = Visual::create(m_spGeometry, m_spMaterial);
		return spVisual;
	}

	Visual::Visual(const std::shared_ptr<Geometry>& spGeometry, const std::shared_ptr<Material>& spMaterial)
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