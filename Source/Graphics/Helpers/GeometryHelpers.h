#pragma once

#include <Graphics/StaticGeometry.h>

namespace baselib 
{
	namespace graphics
	{
		//! Create and return a static quad geometry.
		std::shared_ptr<StaticGeometry> createQuadGeometry();
	}
}