#include "DirectionalLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight() :
		OrthoCameraLight(LightType::DIRECTIONAL)
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &lightParamSetter) noexcept
	{
		LightBaseComponent::_onDeploy(lightParamSetter);
		_deployDirection(lightParamSetter);
	}
}
