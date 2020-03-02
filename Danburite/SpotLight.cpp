#include "SpotLight.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SpotLight::SpotLight(UniformSetter &uniformSetter) noexcept :
		PointLight(uniformSetter, LightType::SPOT)
	{}

	void SpotLight::_onDeploy(LightUniformSetter &target) noexcept
	{
		PointLight::_onDeploy(target);
		DirectionalLightComponent::_onDeploy(target);
		SpotLightComponent::_onDeploy(target);
	}

	void SpotLight::bakeDepthMap() noexcept
	{

	}
}