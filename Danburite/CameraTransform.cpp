#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onValidateTranslation(mat4 &translationMat) const noexcept
	{
		Transform::_onValidateTranslation(translationMat);
		__viewTranslationMat = translate(-getPosition());
	}

	void CameraTransform::_onValidateRotation(mat4 &rotationMat) const noexcept
	{
		const vec3 &rotation = getRotation();

		__viewRotationMat = eulerAngleXYZ(-rotation.x, -rotation.y, -rotation.z);
		rotationMat = transpose(__viewRotationMat);	// == inverse
	}

	const mat4 &CameraTransform::getViewTranslationMatrix() const noexcept
	{
		_validateTranslation();
		return __viewTranslationMat;
	}

	const mat4 &CameraTransform::getViewRotationMatrix() const noexcept
	{
		_validateRotation();
		return __viewRotationMat;
	}

	const mat4 &CameraTransform::getViewMatrix() const noexcept
	{
		if (_getPositionDirty() || _getRotationDirty())
			__viewMat = (getViewRotationMatrix() * getViewTranslationMatrix());

		return __viewMat;
	}
}