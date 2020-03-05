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
			__rotationMat = eulerAngleXYZ(__rotation.x, __rotation.y, __rotation.z);
			__rotationDirty = false;
		}
	}

	void Transform::moveForward(const float delta) noexcept
	{
		__validateRotationMat();

		__positionDirty = true;

		const vec4 &forward = __rotationMat[2];

		__position.x += (forward.x * delta);
		__position.y += (forward.y * delta);
		__position.z += (forward.z * delta);
	}

	void Transform::moveHorizontal(const float delta) noexcept
	{
		__validateRotationMat();

		__positionDirty = true;

		const vec4 &right = __rotationMat[0];

		__position.x += (right.x * delta);
		__position.y += (right.y * delta);
		__position.z += (right.z * delta);
	}

	void Transform::moveVertical(const float delta) noexcept
	{
		__validateRotationMat();

		__positionDirty = true;

		const vec4 &up = __rotationMat[1];

		__position.x += (up.x * delta);
		__position.y += (up.y * delta);
		__position.z += (up.z * delta);
	}

	void Transform::orbit(const float angle, const vec3 &pivot, const vec3 &axis, const bool angleRotation) noexcept
	{
		__positionDirty = true;

		const mat4 &rotationMat = rotate(angle, axis);

		vec3 movedPos = (__position - pivot);
		movedPos = (mat3 { rotationMat } * movedPos);

		__position = (movedPos + pivot);

		if (angleRotation)
		{
			__rotationDirty = true;
			__rotation += eulerAngles(angleAxis(angle, axis));
		}
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