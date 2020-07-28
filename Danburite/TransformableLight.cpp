#include "TransformableLight.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	TransformableLight::TransformableLight(
		const LightType type, const DepthBakingType depthBakingType, const GLuint index) :
		Light(type, depthBakingType, index)
	{}

	void TransformableLight::_deployDirection(LightUniformSetter &lightSetter) const noexcept
	{
		const Transform &transform = getTransform();
		const vec4 &forward = transform.getForward();

		lightSetter.setUniformVec3(
			ShaderIdentifier::Name::Light::DIRECTION, -forward.x, -forward.y, -forward.z);
	}

	void TransformableLight::_deployPosition(LightUniformSetter &lightSetter) const noexcept
	{
		const Transform &transform = getTransform();
		const vec3 &position = transform.getPosition();

		lightSetter.setUniformVec3(ShaderIdentifier::Name::Light::POSITION, position);
	}
}