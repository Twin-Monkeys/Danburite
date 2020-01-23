#include "DirectionalLightComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void DirectionalLightComponent::_onDeploy(LightUniformSetter &target) noexcept
	{
		target.setUniformVec3(ShaderIdentifier::Name::Light::DIRECTION, __direction);
	}

	const vec3 &DirectionalLightComponent::getDirection() const noexcept
	{
		return __direction;
	}

	void DirectionalLightComponent::setDirection(const vec3 &direction) noexcept
	{
		__direction = normalize(direction);
	}

	void DirectionalLightComponent::setDirection(const float x, const float y, const float z) noexcept
	{
		setDirection({ x, y, z });
	}
}
