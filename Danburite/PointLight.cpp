#include "PointLight.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(const LightType type) :
		PerspectiveLight(type)
	{}

	PointLight::PointLight() :
		PerspectiveLight(LightType::POINT)
	{}

	void PointLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		_deployBaseComponent(lightSetter);
		_deployAttenuatedComponent(lightSetter);
		_deployPosition(lightSetter);
	}
}
