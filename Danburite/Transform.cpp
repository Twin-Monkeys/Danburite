#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	Transform &Transform::moveForward(const float delta) noexcept
	{
		__rotationMat = __rotation.getMatrix();
		const vec4 &forward = getForward();

		return adjustPosition(forward.x * delta, forward.y * delta, forward.z * delta);
	}

	Transform &Transform::moveHorizontal(const float delta) noexcept
	{
		__rotationMat = __rotation.getMatrix();
		const vec4 &horizontal = getHorizontal();

		return adjustPosition(horizontal.x * delta, horizontal.y * delta, horizontal.z * delta);
	}

	Transform &Transform::moveVertical(const float delta) noexcept
	{
		__rotationMat = __rotation.getMatrix();
		const vec4 &vertical = getVertical();

		return adjustPosition(vertical.x * delta, vertical.y * delta, vertical.z * delta);
	}

	Transform &Transform::orient(const vec3 &forward, const vec3 &referenceUp) noexcept
	{
		__rotation.orient(forward, referenceUp);
		return *this;
	}

	Transform &Transform::lookAt(const vec3 &position, const vec3 &target, const vec3 &referenceUp) noexcept
	{
		return setPosition(position).orient(target - position, referenceUp);
	}

	Transform &Transform::orbit(const float angle, const vec3 &pivot, const vec3 &axis, const bool angleRotation) noexcept
	{
		const quat &rotationQuat = angleAxis(angle, normalize(axis));
		__position = ((rotationQuat * (__position - pivot)) + pivot);

		if (angleRotation)
			__rotation.rotateGlobal(angle, axis);

		return *this;
	}

	void Transform::updateMatrix() noexcept
	{
		__scaleMat = scale(__scale);
		__rotationMat = __rotation.getMatrix();
		__translationMat = translate(__position);

		__modelMat = (__translationMat * __rotationMat * __scaleMat);
	}

	mat4 Transform::calcMatrix(const vec3 &position, const Quaternion &rotation, const vec3 &scale) noexcept
	{
		const mat4 &scaleMat		= glm::scale(scale);
		const mat4 &rotationMat		= rotation.getMatrix();
		const mat4 &translationMat	= translate(position);

		return (translationMat * rotationMat * scaleMat);
	}
}