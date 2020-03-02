#include "DirectionalLight.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight(UniformSetter &uniformSetter) noexcept :
		Light(uniformSetter, LightType::DIRECTIONAL)
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &target) noexcept
	{
		LightBaseComponent::_onDeploy(target);
		DirectionalLightComponent::_onDeploy(target);
	}

	void DirectionalLight::bakeDepthMap() noexcept
	{

	}
}
