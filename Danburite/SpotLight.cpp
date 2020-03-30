#include "SpotLight.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SpotLight::SpotLight() :
		PointLight(LightType::SPOT)
	{}

	void SpotLight::_onDeploy(LightUniformSetter &lightParamSetter) noexcept
	{
		PointLight::_onDeploy(lightParamSetter);
		SpotLightComponent::_onDeploy(lightParamSetter);
		_deployDirection(lightParamSetter);
	}
}