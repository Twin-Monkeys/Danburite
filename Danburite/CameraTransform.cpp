#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateRotation(mat4 &rotationMat) const noexcept
	{
		rotationMat = transpose(__viewRotationMat);	// == inverse
	}

	const mat4 &CameraTransform::getViewTranslationMatrix() const noexcept
	{
		return __viewTranslationMat;
	}

	const mat4 &CameraTransform::getViewRotationMatrix() const noexcept
	{
		return __viewRotationMat;
	}

	const mat4 &CameraTransform::getViewMatrix() const noexcept
	{
		return __viewMat;
	}

	void CameraTransform::update() noexcept
	{
		const vec3 &position = getPosition();
		const vec3 &rotation = getRotation();

		__viewTranslationMat = translate(-position);
		__viewRotationMat = eulerAngleXYZ(-rotation.x, -rotation.y, -rotation.z);
		__viewMat = (__viewRotationMat * __viewTranslationMat);

		Transform::update();
	}
}