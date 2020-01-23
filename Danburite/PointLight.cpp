#include "PointLight.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(UniformSetter &uniformSetter, const LightType type) noexcept :
		Light(uniformSetter, type)
	{}

	PointLight::PointLight(UniformSetter &uniformSetter) noexcept :
		Light(uniformSetter, LightType::POINT)
	{}

	void PointLight::_onDeploy(LightUniformSetter &target) noexcept
	{
		LightBaseComponent::_onDeploy(target);
		PositionableLightComponent::_onDeploy(target);
		AttenuatedLightComponent::_onDeploy(target);
	}
}
