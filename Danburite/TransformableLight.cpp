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

	void TransformableLight::_deployDirection(LightUniformInterface &lightUI) const noexcept
	{
		lightUI.direction = { getIndex(), getTransform().getForward() };
	}

	void TransformableLight::_deployPosition(LightUniformInterface &lightUI) const noexcept
	{
		const Transform &transform = getTransform();
		const vec3 &position = transform.getPosition();

		lightUI.pos = { getIndex(), position };
	}
}