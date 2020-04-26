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

	Quaternion &Quaternion::setEulerAngles(const vec3 &eulerAngles) noexcept
	{
		__quaternion = quat { eulerAngles };
		return *this;
	}

	Quaternion &Quaternion::setEulerAngles(const float pitch, const float yaw, const float roll) noexcept
	{
		return setEulerAngles(vec3 { pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotateGlobal(const glm::vec3 &eulerAngles) noexcept
	{
		__quaternion = (quat { eulerAngles } * __quaternion);
		return *this;
	}

	Quaternion &Quaternion::rotateGlobal(const float pitch, const float yaw, const float roll) noexcept
	{
		return rotateGlobal(vec3{ pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotateGlobal(const float angle, const vec3 &axis) noexcept
	{
		__quaternion = (angleAxis(angle, normalize(axis)) * __quaternion);
		return *this;
	}

	Quaternion &Quaternion::rotateLocal(const vec3 &eulerAngles) noexcept
	{
		return rotateLocal(eulerAngles[0], eulerAngles[1], eulerAngles[2]);
	}

	Quaternion &Quaternion::rotateLocal(const float pitch, const float yaw, const float roll) noexcept
	{
		const mat4 &matrix = getMatrix();

		return
			rotateGlobal(pitch, matrix[0]).
			rotateGlobal(yaw, matrix[1]).
			rotateGlobal(roll, matrix[2]);
	}

	Quaternion &Quaternion::rotateFPS(const float pitch, const float yaw, const vec3 &referenceUp) noexcept
	{
		const mat4 &matrix = getMatrix();
		const vec3 &normalizedRefUp = normalize(referenceUp);
		const vec3 &horiz = vec3{ matrix[0] };

		const vec3 &referenceHoriz = (horiz - (dot(normalizedRefUp, horiz) * normalizedRefUp));

		return
			rotateGlobal(pitch, referenceHoriz).
			rotateGlobal(yaw, referenceUp);
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