#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		const vec3 &position = getPosition();
		__viewTranslationMat = translate(-position);

		Transform::_onUpdateTranslationMatrix(translationMat);
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

	void CameraTransform::getViewMatrix(mat4 &retVal) const noexcept
	{
		retVal = (__viewRotationMat * __viewTranslationMat);
	}
}