#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		const vec3 &position = getAnimatedPosition();
		__viewTranslationMat = translate(-position);

		AnimatableTransform::_onUpdateTranslationMatrix(translationMat);
	}

	void CameraTransform::_onUpdateRotationMatrix(mat4 &rotationMat) noexcept
	{
		const vec3 &eularAngles = getAnimatedRotation().getEularAngles();
		__viewRotationMat = eulerAngleXYZ(-eularAngles.x, -eularAngles.y, -eularAngles.z);

		rotationMat = transpose(__viewRotationMat);
	}

	void CameraTransform::updateMatrix(const float deltaTime) noexcept
	{
		AnimatableTransform::updateMatrix(deltaTime);
		__viewMat = (__viewRotationMat * __viewTranslationMat);
	}
}