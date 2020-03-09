#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void Transform::_validateTranslation() const noexcept
	{
		if (__positionDirty)
		{
			_onValidateTranslation(__translationMat);
			__positionDirty = false;
		}
	}

	void Transform::_validateScale() const noexcept
	{
		if (__scaleDirty)
		{
			_onValidateScale(__scaleMat);
			__scaleDirty = false;
		}
	}

	void Transform::_validateRotation() const noexcept
	{
		if (__rotationDirty)
		{
			_onValidateRotation(__rotationMat);
			__rotationDirty = false;
		}
	}

	void Transform::_onValidateTranslation(mat4 &translationMat) const noexcept
	{
		translationMat = translate(__position);
	}

	void Transform::_onValidateScale(mat4 &scaleMat) const noexcept
	{
		scaleMat = scale(__scale);
	}

	void Transform::_onValidateRotation(mat4 &rotationMat) const noexcept
	{
		rotationMat = eulerAngleXYZ(__rotation.x, __rotation.y, __rotation.z);
	}

	void Transform::moveForward(const float delta) noexcept
	{
		__positionDirty = true;

		const vec4 &forward = getForward();
		__position.x += (forward.x * delta);
		__position.y += (forward.y * delta);
		__position.z += (forward.z * delta);
	}

	void Transform::moveHorizontal(const float delta) noexcept
	{
		__positionDirty = true;

		const vec4 &horizontal = getHorizontal();
		__position.x += (horizontal.x * delta);
		__position.y += (horizontal.y * delta);
		__position.z += (horizontal.z * delta);
	}

	void Transform::moveVertical(const float delta) noexcept
	{
		__positionDirty = true;

		const vec4 &vertical = getVertical();
		__position.x += (vertical.x * delta);
		__position.y += (vertical.y * delta);
		__position.z += (vertical.z * delta);
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

	const vec4 &Transform::getForward() const noexcept
	{
		return getRotationMatrix()[2];
	}

	const vec4 &Transform::getHorizontal() const noexcept
	{
		return getRotationMatrix()[0];
	}

	const vec4 &Transform::getVertical() const noexcept
	{
		return getRotationMatrix()[1];
	}

	const mat4 &Transform::getTranslationMatrix() const noexcept
	{
		_validateTranslation();
		return __translationMat;
	}

	const mat4 &Transform::getScaleMatrix() const noexcept
	{
		_validateScale();
		return __scaleMat;
	}
	
	const mat4 &Transform::getRotationMatrix() const noexcept
	{
		_validateRotation();
		return __rotationMat;
	}

	const mat4 &Transform::getModelMatrix() const noexcept
	{
		if (_getPositionDirty() || _getScaleDirty() || _getRotationDirty())
			__modelMat = (getTranslationMatrix() * getRotationMatrix() * getScaleMatrix());

		return __modelMat;
	}
}