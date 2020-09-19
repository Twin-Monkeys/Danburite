#include "Quaternion.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	Quaternion::Quaternion(const Quaternion &src) noexcept
	{
		set(src);
	}

	Quaternion::Quaternion(const quat &src) noexcept
	{
		set(src);
	}

	Quaternion::Quaternion(const float w, const float x, const float y, const float z) noexcept
	{
		set(w, x, y, z);
	}

	Quaternion::Quaternion(const vec3 &eulerAngles, const EulerAngleOrder rotationOrder) noexcept
	{
		set(eulerAngles, rotationOrder);
	}

	Quaternion::Quaternion(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder) noexcept
	{
		set(pitch, yaw, roll, rotationOrder);
	}

	Quaternion::Quaternion(const float angle, const vec3 &axis) noexcept
	{
		set(angle, axis);
	}

	Quaternion::Quaternion(const mat3 &rotationMatrix) noexcept
	{
		set(rotationMatrix);
	}

	Quaternion::Quaternion(const mat4 &rotationMatrix) noexcept
	{
		set(rotationMatrix);
	}

	Quaternion &Quaternion::set(const quat &src) noexcept
	{
		__quaternion = src;
		return *this;
	}

	Quaternion &Quaternion::set(const float w, const float x, const float y, const float z) noexcept
	{
		return set(quat { w, x, y, z });
	}

	Quaternion &Quaternion::set(const Quaternion &src) noexcept
	{
		return set(src.__quaternion);
	}

	Quaternion &Quaternion::setFromPitch(const float pitch) noexcept
	{
		const float halfPitch = (pitch * .5f);

		set(cosf(halfPitch), sinf(halfPitch), 0.f, 0.f);
		return *this;
	}

	Quaternion &Quaternion::setFromYaw(const float yaw) noexcept
	{
		const float halfYaw = (yaw * .5f);

		set(cosf(halfYaw), 0.f, sinf(halfYaw), 0.f);
		return *this;
	}

	Quaternion &Quaternion::setFromRoll(const float roll) noexcept
	{
		const float halfRoll = (roll * .5f);

		set(cosf(halfRoll), 0.f, 0.f, sinf(halfRoll));
		return *this;
	}

	Quaternion &Quaternion::set(const vec3 &eulerAngles, const EulerAngleOrder rotationOrder) noexcept
	{
		const vec3 &halfAngleCos = glm::cos(eulerAngles * .5f);
		const vec3 &halfAngleSin = glm::sin(eulerAngles * .5f);

		const Quaternion pitchYawRollQuat[] =
		{
			{ halfAngleCos.x, halfAngleSin.x, 0.f, 0.f },
			{ halfAngleCos.y, 0.f, halfAngleSin.y, 0.f },
			{ halfAngleCos.z, 0.f, 0.f, halfAngleSin.z }
		};

		const unsigned (&orderArr)[3] = enumToArr(rotationOrder);
		return set(pitchYawRollQuat[orderArr[2]] * pitchYawRollQuat[orderArr[1]] * pitchYawRollQuat[orderArr[0]]);
	}

	Quaternion &Quaternion::set(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder) noexcept
	{
		return set(vec3 { pitch, yaw, roll }, rotationOrder);
	}

	Quaternion &Quaternion::set(const float angle, const vec3 &axis) noexcept
	{
		return set(angleAxis(angle, normalize(axis)));
	}

	Quaternion &Quaternion::set(const mat3 &rotationMatrix) noexcept
	{
		return set(quat { rotationMatrix });
	}

	Quaternion &Quaternion::set(const mat4 &rotationMatrix) noexcept
	{
		return set(quat { rotationMatrix });
	}

	Quaternion &Quaternion::orient(const vec3 &forward, const vec3 &referenceUp) noexcept
	{
		const vec3 &normalizedForward = normalize(forward);
        const vec3 &normalizedRefUp = normalize(referenceUp);

        const vec3 &horizontal = normalize(cross(normalizedRefUp, normalizedForward));
        const vec3 &vertical = normalize(cross(normalizedForward, horizontal));

        __quaternion = mat3 { horizontal, vertical, normalizedForward };
        return *this;
	}

	Quaternion &Quaternion::rotateGlobalPitch(const float pitch) noexcept
	{
		*this = (Quaternion{}.setFromPitch(pitch) *(*this));
		return *this;
	}

	Quaternion &Quaternion::rotateGlobalYaw(const float yaw) noexcept
	{
		*this = (Quaternion{}.setFromYaw(yaw) * (*this));
		return *this;
	}

	Quaternion &Quaternion::rotateGlobalRoll(const float roll) noexcept
	{
		*this = (Quaternion{}.setFromRoll(roll) * (*this));
		return *this;
	}

	Quaternion &Quaternion::rotateGlobal(const vec3 &eulerAngles, const EulerAngleOrder rotationOrder) noexcept
	{
		*this = (Quaternion { eulerAngles, rotationOrder } * (*this));
		return *this;
	}

	Quaternion &Quaternion::rotateGlobal(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder) noexcept
	{
		return rotateGlobal(vec3 { pitch, yaw, roll }, rotationOrder);
	}

	Quaternion &Quaternion::rotateGlobal(const float angle, const vec3 &axis) noexcept
	{
		return set(angleAxis(angle, normalize(axis)) * __quaternion);
	}

	Quaternion &Quaternion::rotateLocalPitch(const float pitch) noexcept
	{
		const mat4 &basis = getMatrix();
		return rotateGlobal(pitch, basis[0]);
	}

	Quaternion &Quaternion::rotateLocalYaw(const float yaw) noexcept
	{
		const mat4& basis = getMatrix();
		return rotateGlobal(yaw, basis[1]);
	}

	Quaternion &Quaternion::rotateLocalRoll(const float roll) noexcept
	{
		const mat4& basis = getMatrix();
		return rotateGlobal(roll, basis[2]);
	}

	Quaternion &Quaternion::rotateLocal(const vec3 &eulerAngles, const EulerAngleOrder rotationOrder) noexcept
	{
		const mat4 &basis = getMatrix();

		const Quaternion pitchYawRollQuat[] =
		{
			{ eulerAngles[0], basis[0] },
			{ eulerAngles[1], basis[1] },
			{ eulerAngles[2], basis[2] }
		};

		const unsigned(&orderArr)[3] = enumToArr(rotationOrder);
		*this = ((pitchYawRollQuat[orderArr[2]] * pitchYawRollQuat[orderArr[1]] * pitchYawRollQuat[orderArr[0]]) * (*this));
		return *this;
	}

	Quaternion &Quaternion::rotateLocal(const float pitch, const float yaw, const float roll, const EulerAngleOrder rotationOrder) noexcept
	{
		return rotateLocal(vec3 { pitch, yaw, roll }, rotationOrder);
	}

	Quaternion &Quaternion::rotateFPSPitch(const float pitch, const vec3& referenceUp) noexcept
	{
		const mat4 &matrix = getMatrix();
		const vec3 &normalizedRefUp = normalize(referenceUp);
		const vec3 &horiz = vec3 { matrix[0] };

		// not normalized
		const vec3 &referenceHoriz = (horiz - (dot(normalizedRefUp, horiz) * normalizedRefUp));
		return rotateGlobal(pitch, referenceHoriz);
	}

	Quaternion &Quaternion::rotateFPSYaw(const float yaw, const vec3& referenceUp) noexcept
	{
		return rotateGlobal(yaw, referenceUp);
	}

	vec3 Quaternion::getEularAngles() const noexcept
	{
		return eulerAngles(__quaternion);
	}

	mat4 Quaternion::getMatrix() const noexcept
	{
		return mat4_cast(__quaternion);
	}

	Quaternion Quaternion::inverse() const noexcept
	{
		return glm::inverse(__quaternion);
	}

	pair<float, vec3> Quaternion::getAngleAxis() const noexcept
	{
		return { angle(__quaternion), axis(__quaternion) };
	}

	Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs) noexcept
	{
		return (lhs.__quaternion * rhs.__quaternion);
	}

	Quaternion operator-(const Quaternion &quat) noexcept
	{
		return -quat.__quaternion;
	}

	Quaternion Quaternion::slerp(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept
	{
		return glm::slerp(lhs.__quaternion, rhs.__quaternion, weight);
	}
}