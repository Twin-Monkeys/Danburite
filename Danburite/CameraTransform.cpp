#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		Transform::_onUpdateTranslationMatrix(translationMat);
		const vec4 &position = translationMat[3];

		__viewTranslationMat[3].x = -position.x;
		__viewTranslationMat[3].y = -position.y;
		__viewTranslationMat[3].z = -position.z;
	}

	void CameraTransform::_onUpdateRotationMatrix(mat4 &rotationMat) noexcept
	{
		const vec3 &eularAngles = getRotation().getEularAngles();
		__viewRotationMat = eulerAngleXYZ(-eularAngles.x, -eularAngles.y, -eularAngles.z);

		// == inverse
		rotationMat = transpose(__viewRotationMat);
	}

	mat4 CameraTransform::getViewMatrix() const noexcept
	{
		return (__viewRotationMat * __viewTranslationMat);
	}
}