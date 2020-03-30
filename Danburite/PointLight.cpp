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

	void PointLight::_onDeploy(LightUniformSetter &lightParamSetter) noexcept
	{
		LightBaseComponent::_onDeploy(lightParamSetter);
		AttenuatedLightComponent::_onDeploy(lightParamSetter);
		_deployPosition(lightParamSetter);
	}
}
