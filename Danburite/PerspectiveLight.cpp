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
		__depthBaker.bind();
		drawer.batchRawDrawCall();
		__depthBaker.unbind();
	}

	void PerspectiveLight::setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setResolution(width, height);
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

		/*const mat4& viewMat = __camera.getViewMatrix();
		const mat4& projMat = __camera.getProjectionMatrix();

		__depthBaker.setProjViewMatrix(projMat * viewMat);*/
	}
}