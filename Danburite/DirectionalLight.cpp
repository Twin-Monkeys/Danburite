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
		_deployBaseComponent(lightSetter);
		_deployDirection(lightSetter);
	}

	void DirectionalLight::volumeDrawcall() noexcept
	{
		__fullscreenDrawer.draw();
	}
}
