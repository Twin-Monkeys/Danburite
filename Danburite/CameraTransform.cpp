#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		__viewTranslationMat = translate(-getAnimatedPosition());
		Transform::_onUpdateTranslationMatrix(translationMat);
	}

	void CameraTransform::_onUpdateRotationMatrix(mat4 &rotationMat) noexcept
	{
		const vec3 &animatedEularAngles = getAnimatedRotation().getEularAngles();
		const vec3 &eularAngles = getRotation().getEularAngles();

		__viewRotationMat =
			eulerAngleXYZ(-animatedEularAngles.x, -animatedEularAngles.y, -animatedEularAngles.z);

		rotationMat = transpose(
			eulerAngleXYZ(-eularAngles.x, -eularAngles.y, -eularAngles.z));
	}

	void CameraTransform::updateMatrix(const float deltaTime) noexcept
	{
		AnimatableTransform::updateMatrix(deltaTime);
		__viewMat = (__viewRotationMat * __viewTranslationMat);
	}
}