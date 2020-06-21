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
		Transform::_onUpdateRotationMatrix(rotationMat);
		__viewRotationMat = transpose(rotationMat);
	}

	void CameraTransform::updateMatrix() noexcept
	{
		Transform::updateMatrix();
		__viewMat = (__viewRotationMat * __viewTranslationMat);
	}
}