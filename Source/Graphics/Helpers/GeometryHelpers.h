#pragma once

#include <Graphics/StaticGeometry.h>

namespace baselib 
{
	namespace graphics
	{
		//! Create a unit quad.
		std::shared_ptr<StaticGeometry> createQuad();

		/*! Create a grid of lines.
		 *	iLines is the number of lines from the centre of the grid to the edge (excluding the centre line).
		 *	In other words, the total number of lines along an axis will be iLines*2 + 1.
		 *	fLineSpacing is the distance between any 2 given parallel lines.
		 *  xzPlane, xyPlane and yzPlane bools indicate whether the grid lines should fill the given plane or not.
		 */
		std::shared_ptr<StaticGeometry> createGrid(int iLines, float fLineSpacing, bool xzPlane = true, bool xyPlane = false, bool yzPlane = false);
	}
}