#include "PerspectiveLight.h"

using namespace ObjectGL;

namespace Danburite
{
	PerspectiveLight::PerspectiveLight(const LightType type) :
		TransformableLight(type)
	{}

	void PerspectiveLight::_onDeployShadowData(LightUniformSetter &lightSetter) noexcept
	{

	}

	void PerspectiveLight::_onBakeDepthMap(Drawer &drawer) noexcept
	{

	}

	void PerspectiveLight::setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept
	{

	}

	Transform &PerspectiveLight::getTransform() noexcept
	{
		return __transform;
	}

	const Transform &PerspectiveLight::getTransform() const noexcept
	{
		return __transform;
	}

	void PerspectiveLight::update() noexcept
	{
		__transform.update();
	}
}