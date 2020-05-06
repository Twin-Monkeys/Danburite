#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		Transform::_onUpdateTranslationMatrix(translationMat);

		vec4 &position = translationMat[3];
		vec4 &viewTranslation = __viewTranslationMat[3];

		for (length_t i = 0; i <= 2; i++)
			viewTranslation[i] = -position[i];
	}

	void CameraTransform::_onUpdateRotationMatrix(mat4 &rotationMat) noexcept
	{
		const vec3 &eularAngles = getRotation().getEularAngles();
		__viewRotationMat = eulerAngleXYZ(-eularAngles.x, -eularAngles.y, -eularAngles.z);

		rotationMat = transpose(__viewRotationMat);
	}

	void CameraTransform::updateMatrix(const float deltaTime) noexcept
	{
		Transform::updateMatrix(deltaTime);
		__viewMat = (__viewRotationMat * __viewTranslationMat);
	}
}