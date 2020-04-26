#include "Quaternion.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	vec3 Quaternion::getEularAngles() const noexcept
	{
		return eulerAngles(__quaternion);
	}

	void Quaternion::getEularAngles(vec3 &retVal) const noexcept
	{
		retVal = eulerAngles(__quaternion);
	}

	Quaternion &Quaternion::set(const vec3 &eularAngles) noexcept
	{
		__quaternion = quat { eularAngles };
		return *this;
	}

	Quaternion &Quaternion::set(const float pitch, const float yaw, const float roll) noexcept
	{
		return set(vec3 { pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotate(const glm::vec3 &eularAngles) noexcept
	{
		__quaternion = (quat { eularAngles } * __quaternion);
		return *this;
	}

	Quaternion &Quaternion::rotate(const float pitch, const float yaw, const float roll) noexcept
	{
		return rotate(vec3{ pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotate(const float angle, const vec3 &axis) noexcept
	{
		__quaternion = (angleAxis(angle, normalize(axis)) * __quaternion);
		return *this;
	}

	Quaternion &Quaternion::adjustFPSPitch(const float pitch, const vec3 &referenceUp) noexcept
	{
		const mat4 &matrix = getMatrix();
		const vec3 &normalizedRefUp = normalize(referenceUp);
		const vec3 &horiz = vec3{ matrix[0] };
		const vec3 &referenceHoriz = (horiz - (dot(normalizedRefUp, horiz) * normalizedRefUp));

		return rotate(pitch, referenceHoriz);
	}

	Quaternion &Quaternion::adjustFPSYaw(const float yaw, const vec3 &referenceUp) noexcept
	{
		return rotate(yaw, referenceUp);
	}

	mat4 Quaternion::getMatrix() const noexcept
	{
		return mat4_cast(__quaternion);
	}

	void Quaternion::getMatrix(mat4 &retVal) const noexcept
	{
		retVal = mat4_cast(__quaternion);
	}
}