#include "DirectionalLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight() :
		OrthoLight(LightType::DIRECTIONAL)
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		LightBaseComponent::_onDeploy(lightSetter);
		_deployDirection(lightSetter);
	}
}
