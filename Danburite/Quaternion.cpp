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

	Quaternion::Quaternion(const vec3 &eulerAngles) noexcept
	{
		set(eulerAngles);
	}

	Quaternion::Quaternion(const float pitch, const float yaw, const float roll) noexcept
	{
		set(pitch, yaw, roll);
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
		__quaternion = normalize(src);
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

	Quaternion &Quaternion::set(const vec3 &eulerAngles) noexcept
	{
		return set(quat { eulerAngles });
	}

	Quaternion &Quaternion::set(const float pitch, const float yaw, const float roll) noexcept
	{
		return set(vec3 { pitch, yaw, roll });
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

	Quaternion &Quaternion::rotateGlobal(const vec3 &eulerAngles) noexcept
	{
		return set(quat { eulerAngles } * __quaternion);
	}

	Quaternion &Quaternion::rotateGlobal(const float pitch, const float yaw, const float roll) noexcept
	{
		return rotateGlobal(vec3{ pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotateGlobal(const float angle, const vec3 &axis) noexcept
	{
		return set(angleAxis(angle, normalize(axis)) * __quaternion);
	}

	Quaternion &Quaternion::rotateLocal(const vec3 &eulerAngles) noexcept
	{
		const mat4 &basis = getMatrix();

		return set(
			angleAxis(eulerAngles[2], vec3{ basis[2] }) *
			angleAxis(eulerAngles[1], vec3{ basis[1] }) *
			angleAxis(eulerAngles[0], vec3{ basis[0] }) *
			__quaternion);
	}

	Quaternion &Quaternion::rotateLocal(const float pitch, const float yaw, const float roll) noexcept
	{
		return rotateLocal(vec3 { pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotateFPS(const float pitch, const float yaw, const vec3 &referenceUp) noexcept
	{
		const mat4 &matrix = getMatrix();
		const vec3 &normalizedRefUp = normalize(referenceUp);
		const vec3 &horiz = vec3 { matrix[0] };

		// not normalized
		const vec3 &referenceHoriz = (horiz - (dot(normalizedRefUp, horiz) * normalizedRefUp));

		return
			rotateGlobal(pitch, referenceHoriz).
			rotateGlobal(yaw, referenceUp);
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
		return normalize(lhs.__quaternion * rhs.__quaternion);
	}

	Quaternion Quaternion::slerp(const Quaternion &lhs, const Quaternion &rhs, const float weight) noexcept
	{
		return glm::slerp(lhs.__quaternion, rhs.__quaternion, weight);
	}
}