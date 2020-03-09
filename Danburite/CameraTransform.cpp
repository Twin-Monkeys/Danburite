#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onValidateTranslation() const noexcept
	{
		Transform::_onValidateTranslation();
		__viewTranslationMat = translate(-getPosition());
	}

	void CameraTransform::_onValidateRotation() const noexcept
	{
		Transform::_onValidateRotation();
		
		const vec3 &rotation = getRotation();
		__viewRotationMat		= eulerAngleXYZ(-rotation.x, -rotation.y, -rotation.z);
		__viewRotationInvMat	= transpose(__viewRotationMat);	// == inverse
	}

	const vec4 &CameraTransform::getForward() const noexcept
	{
		return getViewRotationInvMatrix()[2];
	}

	const vec4 &CameraTransform::getHorizontal() const noexcept
	{
		return getViewRotationInvMatrix()[0];
	}

	const vec4 &CameraTransform::getVertical() const noexcept
	{
		return getViewRotationInvMatrix()[1];
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

	const mat4 &CameraTransform::getViewRotationInvMatrix() const noexcept
	{
		_validateRotation();
		return __viewRotationInvMat;
	}

	const mat4 &CameraTransform::getViewMatrix() const noexcept
	{
		if (_getPositionDirty() || _getRotationDirty())
			__viewMat = (getViewRotationMatrix() * getViewTranslationMatrix());

		return __viewMat;
	}
}