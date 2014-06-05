#include "MathHelpers.h"

namespace baselib {

	void calcQuatWComponent(glm::quat &q) 
	{
		float t = 1.0f - q.x*q.x - q.y*q.y - q.z*q.z;
		q.w = (t < 0.0f) ? 0.0f : -sqrt(t);
	}

	glm::quat multiplyQuat(const glm::quat &q1, const glm::quat &q2) 
	{
		Vec3 v1(q1.x, q1.y, q1.z);
		Vec3 v2(q2.x, q2.y, q2.z);

		float s = q1.w*q2.w - glm::dot(v1,v2);
		Vec3 v = (glm::cross(v1,v2) + (v2*q1.w) ) + (v1*q2.w);

		return glm::quat(s, v.x, v.y, v.z);
	}

	glm::quat slerpQuat(const glm::quat &q1, const glm::quat &q2, float u) 
	{
		float cosOmega = glm::dot(q1, q2);
		glm::quat q2flipped = q2;
		if (cosOmega < 0.0f) 
		{
			q2flipped *= -1;
			cosOmega *= -1;
		}

		float k0, k1;
		//if small angle then do norml linear interp. instead of spherical
		if (cosOmega > 0.99999f) 
		{ 
			k0 = 1.0f - u;
			k1 = u;
		}
		else 
		{
			float sinOmega = sqrt(1.0f - cosOmega*cosOmega);
			float omega = atan2(sinOmega, cosOmega);

			float sinOmegaInv = 1.0f/sinOmega;

			k0 = sin((1.0f - u)*omega)*sinOmegaInv;
			k1 = sin(u*omega)*sinOmegaInv;
		}

		glm::quat result(q1.w*k0 + q2flipped.w*k1, q1.x*k0 + q2flipped.x*k1, q1.y*k0 + q2flipped.y*k1, q1.z*k0 + q2flipped.z*k1);
		result = glm::normalize(result);
		return result;
	}

	float toRad(float deg)
	{
		return deg*PI/180.0f;
	}

	float toDeg(float rad)
	{
		return rad*180.0f/PI;
	}
}