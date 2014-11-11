#pragma once

#include <Graphics/StaticGeometry.h>

namespace baselib 
{
	namespace graphics
	{
		//! Create and return a static quad geometry.
		boost::shared_ptr<StaticGeometry> createQuadGeometry();
	}
}