#include "TransformableLight.h"
#include "ShaderIdentifier.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	TransformableLight::TransformableLight(
		const LightType type, const LightVolumeType volumeType,
		const DepthBakingType depthBakingType, const GLuint index) :
		Light(type, volumeType, depthBakingType, index)
	{}

	void TransformableLight::_deployDirection(DeferredUniformBuffer<LightUniformInterface> &lightUB) const noexcept
	{
		const Transform &transform = getTransform();
		const vec4 &forward = transform.getForward();

		lightUB.getInterface().direction.set(getIndex(), forward);
	}

	void TransformableLight::_deployPosition(DeferredUniformBuffer<LightUniformInterface> &lightUB) const noexcept
	{
		const Transform &transform = getTransform();
		const vec3 &position = transform.getPosition();

		lightUB.getInterface().pos.set(getIndex(), position);
	}
}