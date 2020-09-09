#include "PerspectiveLight.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderIdentifier.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	PerspectiveLight::PerspectiveLight(const LightType type, const GLuint index) :
		TransformableLight(type, LightVolumeType::GEOMETRY, DepthBakingType::CUBEMAP, index)
	{}

	void PerspectiveLight::_onDeployShadowData(LightUniformInterface &lightUI) noexcept
	{
		lightUI.depthMap = { getIndex(), __depthBaker.getDepthMapHandle() };
		lightUI.zFar = { getIndex(), __zFar };
	}

	void PerspectiveLight::_onBakeDepthMap(BatchProcessor<SceneObject> &drawer) noexcept
	{
		__depthBaker.bind();
		drawer.process(&SceneObject::rawDrawcall);
		__depthBaker.unbind();
	}

	const ivec2 &PerspectiveLight::getDepthMapSize() noexcept
	{
		return __depthBaker.getDepthMapSize();
	}

	void PerspectiveLight::setDepthMapSize(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setDepthMapSize(width, height);
	}

	void PerspectiveLight::_onChangeShadowEnabled(const bool enabled) noexcept
	{
		__depthBaker.setEnabled(enabled);
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