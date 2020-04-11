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
		const mat4 &viewMat = __camera.getViewMatrix();
		const mat4 &projMat = __camera.getProjectionMatrix();

		lightSetter.setUniformMat4(
			ShaderIdentifier::Name::Light::PROJ_VIEW_MATRIX, projMat * viewMat);

		lightSetter.setUniformUvec2(
			ShaderIdentifier::Name::Light::DEPTH_MAP, __depthBaker.getDepthMapHandle());
	}

	void OrthoLight::_onBakeDepthMap(Drawer &drawer) noexcept
	{
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

		const mat4& viewMat = __camera.getViewMatrix();
		const mat4& projMat = __camera.getProjectionMatrix();

		__depthBaker.setProjViewMatrix(projMat * viewMat);
	}
}