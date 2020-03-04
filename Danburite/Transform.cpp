#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void Transform::__validateTranslationMat() noexcept
	{
		if (__positionDirty)
		{
			__translationMat = translate(__position);
			__positionDirty = false;
		}
	}

	void Transform::__validateScaleMat() noexcept
	{
		if (__scaleDirty)
		{
			__scaleMat = scale(__scale);
			__scaleDirty = false;
		}
	}

	void Transform::__validateRotationMat() noexcept
	{
		if (__rotationDirty)
		{
			// __rotationMat = mat4_cast(quat{ __rotation });
			__rotationMat = mat4_cast(quat { vec3 { __rotation.x, 0.f , 0.f } } * quat{ vec3 {0.f, __rotation.y, 0.f } } * quat{ vec3 {0.f, 0.f, __rotation.z } });
			__rotationDirty = false;
		}
	}

	void Transform::moveForward(const float delta) noexcept
	{
		__validateRotationMat();

		__positionDirty = true;

		const glm::vec3 direction { row(__rotationMat, 2) };
		__position -= (direction * delta);
	}

	void Transform::moveHorizontal(const float delta) noexcept
	{
		__validateRotationMat();

		__positionDirty = true;

		const glm::vec3 right { row(__rotationMat, 0) };
		__position += (right * delta);
	}

	void Transform::moveVertical(const float delta) noexcept
	{
		__validateRotationMat();

		__positionDirty = true;

		const glm::vec3 up { row(__rotationMat, 1) };
		__position += (up * delta);
	}

	void Transform::orbit(const float angle, const vec3 &pivot, const vec3 &axis) noexcept
	{
		__positionDirty = true;

		const mat4 &rotationMat = rotate(angle, axis);

		vec3 movedPos = (__position - pivot);
		movedPos = (mat3 { rotationMat } * movedPos);

		__position = (movedPos + pivot);
	}

	const mat4 &Transform::getTranslationMatrix() noexcept
	{
		__validateTranslationMat();
		return __translationMat;
	}

	const mat4 &Transform::getScaleMatrix() noexcept
	{
		__validateScaleMat();
		return __scaleMat;
	}
	
	const mat4 &Transform::getRotationMatrix() noexcept
	{
		__validateRotationMat();
		return __rotationMat;
	}

	const mat4 &Transform::getModelMatrix() noexcept
	{
		const bool needToUpdateModelMat =
			(__positionDirty || __scaleDirty || __rotationDirty);

		if (needToUpdateModelMat)
			__modelMat = (getTranslationMatrix() * getRotationMatrix() * getScaleMatrix());

		return __modelMat;
	}
}