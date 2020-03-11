#include "PointLight.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(
		const LightType type, UniformSetter &lightParamSetter, UniformSetter &cameraParamSetter) noexcept :
		PerspectiveCameraLight(type, lightParamSetter, cameraParamSetter)
	{}

	PointLight::PointLight(UniformSetter &lightParamSetter, UniformSetter &cameraParamSetter) noexcept :
		PerspectiveCameraLight(LightType::POINT, lightParamSetter, cameraParamSetter)
	{}

	void PointLight::_onDeploy(LightUniformSetter &lightParamSetter) noexcept
	{
		LightBaseComponent::_onDeploy(lightParamSetter);
		AttenuatedLightComponent::_onDeploy(lightParamSetter);
		_deployPosition(lightParamSetter);
	}
}
