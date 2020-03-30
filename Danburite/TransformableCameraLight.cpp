#include "TransformableCameraLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	TransformableCameraLight::TransformableCameraLight(const LightType type) :
		Light(type)
	{}

	const mat4 &TransformableCameraLight::_getViewMatrix() const noexcept
	{
		return _getCamera().getViewMatrix();
	}

	const mat4 &TransformableCameraLight::_getProjMatrix() const noexcept
	{
		return _getCamera().getProjectionMatrix();
	}

	void TransformableCameraLight::_deployDirection(LightUniformSetter &lightParamSetter) noexcept
	{
		CameraTransform &transform = getTransform();
		const vec4 &forward = transform.getForward();

		lightParamSetter.setUniformVec3(
			ShaderIdentifier::Name::Light::DIRECTION, -forward.x, -forward.y, -forward.z);
	}

	void TransformableCameraLight::_deployPosition(LightUniformSetter &lightParamSetter) noexcept
	{
		CameraTransform &transform = getTransform();
		const vec3 &position = transform.getPosition();

		lightParamSetter.setUniformVec3(ShaderIdentifier::Name::Light::POSITION, position);
	}

	CameraTransform &TransformableCameraLight::getTransform() noexcept
	{
		return _getCamera().getTransform();
	}

	const CameraTransform &TransformableCameraLight::getTransform() const noexcept
	{
		return _getCamera().getTransform();
	}

	void TransformableCameraLight::update() noexcept
	{
		_getCamera().update();
	}
}