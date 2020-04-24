#include "Quaternion.h"
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	vec3 Quaternion::getEularAngles() const noexcept
	{
		return eulerAngles(__quaternion);
	}

	Quaternion &Quaternion::setRotation(const vec3 &eularAngles) noexcept
	{
		__quaternion = quat { eularAngles };
		return *this;
	}

	Quaternion &Quaternion::setRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		return setRotation(vec3 { pitch, yaw, roll });
	}

	Quaternion &Quaternion::adjustRotation(const glm::vec3 &eularAngles) noexcept
	{
		__quaternion = (quat { eularAngles } * __quaternion);
		return *this;
	}

	Quaternion &Quaternion::adjustRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		return adjustRotation(vec3{ pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotate(const float angle, const vec3 &axis) noexcept
	{
		return rotate(angleAxis(angle, axis));
	}

	Quaternion &Quaternion::rotate(const quat &quaternion) noexcept
	{
		__quaternion = (quaternion * __quaternion);
		return *this;
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