#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void Transform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		translationMat = translate(__component.position);
	}

	void Transform::_onUpdateScaleMatrix(mat4 &scaleMat) noexcept
	{
		scaleMat = scale(__component.scale);
	}

	void Transform::_onUpdateRotationMatrix(mat4 &rotationMat) noexcept
	{
		rotationMat = __component.rotation.getMatrix();
	}
	
	Transform &Transform::setRotation(const vec3 &eularAngles) noexcept
	{
		__component.rotation.set(eularAngles);
		return *this;
	}

	Transform &Transform::setRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		__component.rotation.set(pitch, yaw, roll);
		return *this;
	}

	Transform &Transform::setRotation(const Quaternion &rotation) noexcept
	{
		__component.rotation = rotation;
		return *this;
	}

	Transform &Transform::rotateGlobal(const vec3 &eulerAngles) noexcept
	{
		__component.rotation.rotateGlobal(eulerAngles);
		return *this;
	}

	Transform &Transform::rotateGlobal(const float pitch, const float yaw, const float roll) noexcept
	{
		__component.rotation.rotateGlobal(pitch, yaw, roll);
		return *this;
	}

	Transform &Transform::rotateGlobal(const float angle, const vec3 &axis) noexcept
	{
		__component.rotation.rotateGlobal(angle, axis);
		return *this;
	}

	Transform &Transform::rotateLocal(const vec3 &eulerAngles) noexcept
	{
		__component.rotation.rotateLocal(eulerAngles);
		return *this;
	}

	Transform &Transform::rotateLocal(const float pitch, const float yaw, const float roll) noexcept
	{
		__component.rotation.rotateLocal(pitch, yaw, roll);
		return *this;
	}

	Transform &Transform::rotateFPS(const float pitch, const float yaw, const vec3 &referenceUp) noexcept
	{
		__component.rotation.rotateFPS(pitch, yaw, referenceUp);
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

	Transform &Transform::lookAt(const vec3 &forward, const vec3 &referenceUp) noexcept
	{
		__component.rotation.lookAt(forward, referenceUp);
		return *this;
	}

	Transform &Transform::orbit(const float angle, const vec3 &pivot, const vec3 &axis, const bool angleRotation) noexcept
	{
		const quat &rotationQuat = angleAxis(angle, axis);
		__component.position = ((rotationQuat * (__component.position - pivot)) + pivot);

		if (angleRotation)
			__component.rotation.rotateGlobal(angle, axis);

		return *this;
	}

	void Transform::updateMatrix() noexcept
	{
		_onUpdateScaleMatrix(__scaleMat);
		_onUpdateRotationMatrix(__rotationMat);
		_onUpdateTranslationMatrix(__translationMat);

		__modelMat = (__translationMat * __rotationMat * __scaleMat);
	}

	mat4 Transform::calcModelMatrix(const TransformComponent &component) noexcept
	{
		return
		(
			translate(component.position) *
			scale(component.scale) *
			component.rotation.getMatrix()
		);
	}
}