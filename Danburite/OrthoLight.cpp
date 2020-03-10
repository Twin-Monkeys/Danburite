#include "OrthoLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	OrthoLight::OrthoLight(
		const LightType type, UniformSetter &lightParamSetter, UniformSetter &cameraParamSetter) :
		Light(type, lightParamSetter, cameraParamSetter)
	{}

	const mat4 &OrthoLight::_getViewMatrix() const noexcept
	{
		return __camera.getTransform().getViewMatrix();
	}

	const mat4 &OrthoLight::_getProjMatrix() const noexcept
	{
		return __camera;
	}
}