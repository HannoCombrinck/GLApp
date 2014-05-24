#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace baselib
{
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;
	typedef glm::mat4 Mat4;

	const float PI = 3.14159265f;
	const float EPSILON = 1E-6f;

	//! Assumes unit quaternion and calculate w component.
	void calcQuatWComponent(glm::quat &q);
	//! Multiply q1 with q2.
	glm::quat multiplyQuat(glm::quat &q1, glm::quat &q2);
	//! Calculates spherical linear interpolation between quaternions.
	glm::quat slerpQuat(glm::quat &q1, glm::quat &q2, float u);
	//! Converts degrees to radians.
	float toRad(float deg);
	//! Converts radians to degrees
	float toDeg(float rad);

	//! Clamps val between minVal and maxVal.
	template <class T>
	static void clampVal(T& val, T minVal, T maxVal)
	{
		if (val >= maxVal)
			val = maxVal;
		else if (val <= minVal)
			val = minVal;
	}

	//! Smooths current value toward target value.
	template <class T>
	static void smoothTransition(const T& target, T &current, float speed)
	{
		if (glm::length(target - current) > 0.01f)
			current += (target - current)*speed;
		else 
			current = target;
	}
}
