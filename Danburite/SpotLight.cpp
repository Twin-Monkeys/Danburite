#include "SpotLight.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SpotLight::SpotLight() :
		PointLight(LightType::SPOT)
	{}

	void SpotLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		PointLight::_onDeploy(lightSetter);
		SpotLightComponent::_onDeploy(lightSetter);
		_deployDirection(lightSetter);
	}
}