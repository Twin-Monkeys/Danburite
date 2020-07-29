#include "OrthoLight.h"
#include "ShaderIdentifier.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	OrthoLight::OrthoLight(const LightType type, const GLuint index) :
		TransformableLight(type, LightVolumeType::FULLSCREEN, DepthBakingType::ORTHO, index)
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

	void OrthoLight::_onBakeDepthMap(BatchProcessor<Drawable> &drawer) noexcept
	{
		__depthBaker.bind();
		drawer.process(&Drawable::rawDrawcall);
		__depthBaker.unbind();
	}

	const ivec2 &OrthoLight::getDepthMapSize() noexcept
	{
		return __depthBaker.getDepthMapSize();
	}

	void OrthoLight::setDepthMapSize(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setDepthMapSize(width, height);
	}

	void OrthoLight::_onChangeShadowEnabled(const bool enabled) noexcept
	{
		__depthBaker.setEnabled(enabled);
	}

	Transform &OrthoLight::getTransform() noexcept
	{
		return __camera.getTransform();
	}

	const Transform &OrthoLight::getTransform() const noexcept
	{
		return __camera.getTransform();
	}

	void OrthoLight::update(const float deltaTime) noexcept
	{
		__camera.update(deltaTime);

		const mat4 &viewMat = __camera.getViewMatrix();
		const mat4 &projMat = __camera.getProjectionMatrix();

		__depthBaker.setProjViewMatrix(projMat * viewMat);
	}
}