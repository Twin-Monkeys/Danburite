#include "PointLight.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(const LightType type) :
		PerspectiveLight(type)
	{
		setLuminanceTolerance(Constant::Light::AttenuatedComponent::LUMINANCE_TOLERANCE);
	}

	PointLight::PointLight() :
		PerspectiveLight(LightType::POINT)
	{}

	void PointLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		_setValidDistance(
			__luminanceTolerance, getAlbedo(),
			getAmbientStrength(), getDiffuseStrength(), getSpecularStrength());

		_deployBaseComponent(lightSetter);
		_deployAttenuatedComponent(lightSetter);
		_deployPosition(lightSetter);
	}
}
