#include "DirectionalLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight(
		UniformSetter &lightParamSetter, UniformSetter &cameraParamSetter) noexcept :
		OrthoCameraLight(LightType::DIRECTIONAL, lightParamSetter, cameraParamSetter)
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &lightParamSetter) noexcept
	{
		LightBaseComponent::_onDeploy(lightParamSetter);
		_deployDirection(lightParamSetter);
	}
}
