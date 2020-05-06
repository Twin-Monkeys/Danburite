#include "PerspectiveLight.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	PerspectiveLight::PerspectiveLight(const LightType type) :
		TransformableLight(type, DepthBakingType::CUBEMAP)
	{}

	void PerspectiveLight::_onDeployShadowData(LightUniformSetter &lightSetter) noexcept
	{
		lightSetter.setUniformUvec2(
			ShaderIdentifier::Name::Light::DEPTH_MAP, __depthBaker.getDepthMapHandle());

		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::Z_FAR, __zFar);
	}

	void PerspectiveLight::_onBakeDepthMap(Drawer &drawer) noexcept
	{
		__depthBaker.bind();
		drawer.batchRawDrawCall();
		__depthBaker.unbind();
	}

	void PerspectiveLight::setDepthMapSize(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setDepthMapSize(width, height);
	}

	Transform &PerspectiveLight::getTransform() noexcept
	{
		return __transform;
	}

	const Transform &PerspectiveLight::getTransform() const noexcept
	{
		return __transform;
	}

	void PerspectiveLight::update(const float delta) noexcept
	{
		__transform.updateMatrix();

		const vec3 &position = __transform.getPosition();

		const ivec2 &depthMapSize = __depthBaker.getDepthMapSize();
		const float aspectRatio = (float(depthMapSize.x) / float(depthMapSize.y));
	
		const mat4 &projMat = perspective(half_pi<float>(), aspectRatio, __zNear, __zFar);

		__depthBaker.setCenter(position);
		__depthBaker.setFar(__zFar);

		__depthBaker.setProjViewMatrix(
			CubemapSideType::POSITIVE_X,
			projMat * lookAt(position, position + vec3 { 1.f, 0.f, 0.f }, { 0.f, -1.f, 0.f }));

		__depthBaker.setProjViewMatrix(
			CubemapSideType::NEGATIVE_X,
			projMat * lookAt(position, position - vec3 { 1.f, 0.f, 0.f }, { 0.f, -1.f, 0.f }));

		__depthBaker.setProjViewMatrix(
			CubemapSideType::POSITIVE_Y,
			projMat * lookAt(position, position + vec3 { 0.f, 1.f, 0.f }, { 0.f, 0.f, 1.f }));

		__depthBaker.setProjViewMatrix(
			CubemapSideType::NEGATIVE_Y,
			projMat * lookAt(position, position - vec3 { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f }));

		__depthBaker.setProjViewMatrix(
			CubemapSideType::POSITIVE_Z,
			projMat * lookAt(position, position + vec3 { 0.f, 0.f, 1.f }, { 0.f, -1.f, 0.f }));

		__depthBaker.setProjViewMatrix(
			CubemapSideType::NEGATIVE_Z,
			projMat * lookAt(position, position - vec3 { 0.f, 0.f, 1.f }, { 0.f, -1.f, 0.f }));
	}
}