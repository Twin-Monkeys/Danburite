#include "DirectionalLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight(const GLuint index) :
		OrthoLight(LightType::DIRECTIONAL, index),
		__fullscreenDrawer(FullscreenDrawer::getInstance())
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		_deployBaseComponent(lightSetter);
		_deployDirection(lightSetter);
	}

	void DirectionalLight::_onVolumeDrawcall() noexcept
	{
		__fullscreenDrawer.draw();
	}
}
