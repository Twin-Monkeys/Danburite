#include "DirectionalLight.h"
#include "GLFunctionWrapper.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight(const GLuint index) :
		OrthoLight(LightType::DIRECTIONAL, index)
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		_deployBaseComponent(lightSetter);
		_deployDirection(lightSetter);
	}

	void DirectionalLight::_onVolumeDrawcall() noexcept
	{
		GLFunctionWrapper::setCulledFace(FacetType::BACK);
		__fullscreenDrawer.draw();
	}
}
