#include "OrthoLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	OrthoLight::OrthoLight(const LightType type) :
		TransformableLight(type)
	{}

	void OrthoLight::_onDeployShadowData(LightUniformSetter &lightSetter) noexcept
	{
		lightSetter.setUniformMat4(
			ShaderIdentifier::Name::Light::VIEW_MATRIX, __camera.getViewMatrix());

		lightSetter.setUniformMat4(
			ShaderIdentifier::Name::Light::PROJECTION_MATRIX, __camera.getProjectionMatrix());

		lightSetter.setUniformUvec2(
			ShaderIdentifier::Name::Light::DEPTH_MAP, __depthBaker.getDepthMapHandle());
	}

	void OrthoLight::_onBakeDepthMap(Drawer &drawer) noexcept
	{
		const mat4 &viewMat = __camera.getViewMatrix();
		const mat4 &projMat = __camera.getProjectionMatrix();

		__depthBaker.setProjViewMatrix(projMat * viewMat);
		__depthBaker.bind();

		drawer.batchRawDrawCall();

		__depthBaker.unbind();
	}

	void OrthoLight::setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setResolution(width, height);
	}

	Transform &OrthoLight::getTransform() noexcept
	{
		return __camera.getTransform();
	}

	const Transform &OrthoLight::getTransform() const noexcept
	{
		return __camera.getTransform();
	}

	void OrthoLight::update() noexcept
	{
		__camera.update();
	}
}