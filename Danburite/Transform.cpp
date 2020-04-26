#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void Transform::_onUpdateTranslationMatrix(mat4 &translationMat) const noexcept
	{
		translationMat = translate(__position);
	}

	void Transform::_onUpdateScaleMatrix(mat4 &scaleMat) const noexcept
	{
		scaleMat = scale(__scale);
	}

	void Transform::_onUpdateRotationMatrix(mat4 &rotationMat) const noexcept
	{
		__rotation.getMatrix(rotationMat);
	}
	
	Transform &Transform::setRotation(const vec3 &eularAngles) noexcept
	{
		__rotation.set(eularAngles);
		return *this;
	}

	Transform &Transform::setRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		__rotation.set(pitch, yaw, roll);
		return *this;
	}

	Transform &Transform::adjustRotation(const vec3 &eularAngles) noexcept
	{
		__rotation.rotate(eularAngles);
		return *this;
	}

	Transform &Transform::adjustRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		__rotation.rotate(pitch, yaw, roll);
		return *this;
	}

	Transform &Transform::adjustLocalRotation(const vec3 &eularAngles) noexcept
	{
		return adjustLocalRotation(eularAngles.x, eularAngles.y, eularAngles.z);
	}

	Transform &Transform::adjustLocalRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		_onUpdateRotationMatrix(__rotationMat);
		const vec4 &horizontal	= getHorizontal();
		const vec4 &vertical	= getVertical();
		const vec4 &forward		= getForward();

		__rotation.
			rotate(roll, vec3 { forward }).
			rotate(pitch, vec3 { horizontal }).
			rotate(yaw, vec3 { vertical });

		return *this;
	}

	Transform &Transform::adjustFPSPitch(const float pitch, const vec3 &referenceUp) noexcept
	{
		__rotation.adjustFPSPitch(pitch, referenceUp);
		return *this;
	}

	Transform &Transform::adjustFPSYaw(const float yaw, const vec3 &referenceUp) noexcept
	{
		__rotation.adjustFPSYaw(yaw, referenceUp);
		return *this;
	}

	Transform &Transform::adjustFPSRoll(const float roll, const vec3 &referenceUp) noexcept
	{
		__rotation.adjustFPSRoll(roll, referenceUp);
		return *this;
	}

	Transform &Transform::moveForward(const float delta) noexcept
	{
		_onUpdateRotationMatrix(__rotationMat);
		const vec4 &forward = getForward();

		return adjustPosition(forward.x * delta, forward.y * delta, forward.z * delta);
	}

	Transform &Transform::moveHorizontal(const float delta) noexcept
	{
		_onUpdateRotationMatrix(__rotationMat);
		const vec4 &horizontal = getHorizontal();

		return adjustPosition(horizontal.x * delta, horizontal.y * delta, horizontal.z * delta);
	}

	Transform &Transform::moveVertical(const float delta) noexcept
	{
		_onUpdateRotationMatrix(__rotationMat);
		const vec4 &vertical = getVertical();

		return adjustPosition(vertical.x * delta, vertical.y * delta, vertical.z * delta);
	}

	Transform &Transform::orbit(const float angle, const vec3 &pivot, const vec3 &axis, const bool angleRotation) noexcept
	{
		const quat &rotationQuat = angleAxis(angle, axis);
		__position = ((rotationQuat * (__position - pivot)) + pivot);

		if (angleRotation)
			__rotation.rotate(angle, axis);

		return *this;
	}

	void Transform::update() noexcept
	{
		_onUpdateScaleMatrix(__scaleMat);
		_onUpdateRotationMatrix(__rotationMat);
		_onUpdateTranslationMatrix(__translationMat);

		__modelMat = (__translationMat * __rotationMat * __scaleMat);
	}
}