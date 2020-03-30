#include "PointLight.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(const LightType type) :
		PerspectiveCameraLight(type)
	{}

	PointLight::PointLight() :
		PerspectiveCameraLight(LightType::POINT)
	{}

	void PointLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		LightBaseComponent::_onDeploy(lightSetter);
		AttenuatedLightComponent::_onDeploy(lightSetter);
		_deployPosition(lightSetter);
	}
}
