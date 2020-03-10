#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void Transform::_onUpdateTranslation(mat4 &translationMat) const noexcept
	{
		translationMat = translate(__position);
	}

	void Transform::_onUpdateScale(mat4 &scaleMat) const noexcept
	{
		scaleMat = scale(__scale);
	}

	void Transform::_onUpdateRotation(mat4 &rotationMat) const noexcept
	{
		rotationMat = eulerAngleXYZ(__rotation.x, __rotation.y, __rotation.z);
	}

	
	void Transform::moveForward(const float delta) noexcept
	{
		_onUpdateRotation(__rotationMat);

		const vec4 &forward = getForward();
		__position.x += (forward.x * delta);
		__position.y += (forward.y * delta);
		__position.z += (forward.z * delta);
	}

	void Transform::moveHorizontal(const float delta) noexcept
	{
		_onUpdateRotation(__rotationMat);

		const vec4 &horizontal = getHorizontal();
		__position.x += (horizontal.x * delta);
		__position.y += (horizontal.y * delta);
		__position.z += (horizontal.z * delta);
	}

	void Transform::moveVertical(const float delta) noexcept
	{
		_onUpdateRotation(__rotationMat);

		const vec4 &vertical = getVertical();
		__position.x += (vertical.x * delta);
		__position.y += (vertical.y * delta);
		__position.z += (vertical.z * delta);
	}

	void Transform::orbit(const float angle, const vec3 &pivot, const vec3 &axis, const bool angleRotation) noexcept
	{
		const mat4 &rotationMat = rotate(angle, axis);

		vec3 movedPos = (__position - pivot);
		movedPos = (mat3 { rotationMat } * movedPos);

		__position = (movedPos + pivot);

		if (angleRotation)
			__rotation += eulerAngles(angleAxis(angle, axis));
	}

	void Transform::update() noexcept
	{
		_onUpdateTranslation(__translationMat);
		_onUpdateScale(__scaleMat);
		_onUpdateRotation(__rotationMat);

		__modelMat = (__translationMat * __scaleMat * __rotationMat);
	}
}