#pragma once

#include "Math.h"

namespace baselib
{
	//! Assumes unit quaternion and calculate w component.
	void calcQuatWComponent(glm::quat &q);
	//! Multiply q1 with q2.
	glm::quat multiplyQuat(const glm::quat &q1, const glm::quat &q2);
	//! Calculates spherical linear interpolation between quaternions q1 and q2.
	glm::quat slerpQuat(const glm::quat &q1, const glm::quat &q2, float u);
	//! Converts degrees to radians.
	float toRadians(float deg);
	//! Converts radians to degrees
	float toDegrees(float rad);

	//! Clamps val between minVal and maxVal.
	template <class T>
	static void clampVal(T& val, const T minVal, const T maxVal)
	{
		if (val >= maxVal)
			val = maxVal;
		else if (val <= minVal)
			val = minVal;
	}

	//! Smooths current value toward target value.
	template <class T>
	static void smoothTo(T &current, const T& target, float speed)
	{
		if (glm::length(target - current) > 0.01f)
			current += (target - current)*speed;
		else 
			current = target;
	}
}
