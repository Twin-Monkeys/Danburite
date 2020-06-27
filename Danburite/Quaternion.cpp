#include "Quaternion.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	Quaternion::Quaternion(const Quaternion &src, const bool normalization) noexcept
	{
		set(src, normalization);
	}

	Quaternion::Quaternion(const quat &src, const bool normalization) noexcept
	{
		set(src, normalization);
	}

	Quaternion::Quaternion(const float w, const float x, const float y, const float z, const bool normalization) noexcept
	{
		set(w, x, y, z, normalization);
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

	Quaternion::Quaternion(const mat3 &rotationMatrix, const bool normalization) noexcept
	{
		set(rotationMatrix, normalization);
	}

	Quaternion::Quaternion(const mat4 &rotationMatrix, const bool normalization) noexcept
	{
		set(rotationMatrix, normalization);
	}

	Quaternion &Quaternion::set(const quat &src, const bool normalization) noexcept
	{
		__quaternion = src;

		if (normalization)
			__quaternion = normalize(__quaternion);

		return *this;
	}

	Quaternion &Quaternion::set(const float w, const float x, const float y, const float z, const bool normalization) noexcept
	{
		return set(quat { w, x, y, z }, normalization);
	}

	Quaternion &Quaternion::set(const Quaternion &src, const bool normalization) noexcept
	{
		return set(src.__quaternion, normalization);
	}

	Quaternion &Quaternion::set(const vec3 &eulerAngles) noexcept
	{
		return set(quat { eulerAngles }, false);
	}

	Quaternion &Quaternion::set(const float pitch, const float yaw, const float roll) noexcept
	{
		return set(vec3 { pitch, yaw, roll });
	}

	Quaternion &Quaternion::set(const float angle, const vec3 &axis) noexcept
	{
		return set(angleAxis(angle, normalize(axis)), false);
	}

	Quaternion &Quaternion::set(const mat3 &rotationMatrix, const bool normalization) noexcept
	{
		return set(quat { rotationMatrix }, normalization);
	}

	Quaternion &Quaternion::set(const mat4 &rotationMatrix, const bool normalization) noexcept
	{
		return set(quat { rotationMatrix }, normalization);
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
		return set(quat { eulerAngles } * __quaternion, false);
	}

	Quaternion &Quaternion::rotateGlobal(const float pitch, const float yaw, const float roll) noexcept
	{
		return rotateGlobal(vec3{ pitch, yaw, roll });
	}

	Quaternion &Quaternion::rotateGlobal(const float angle, const vec3 &axis) noexcept
	{
		return set(angleAxis(angle, normalize(axis)) * __quaternion, false);
	}

	Quaternion &Quaternion::rotateLocal(const vec3 &eulerAngles) noexcept
	{
		const mat4 &matrix = getMatrix();

		for (length_t i = 0; i < 3; i++)
			rotateGlobal(eulerAngles[i], matrix[i]);

		return *this;
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