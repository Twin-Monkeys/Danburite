#include "PositionableLightComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void PositionableLightComponent::_onDeploy(LightUniformSetter &target) noexcept
	{
		target.setUniformVec3(ShaderIdentifier::Name::Light::POSITION, __pos);
	}

	const vec3 & PositionableLightComponent::getPosition() const noexcept
	{
		return __pos;
	}

	void PositionableLightComponent::setPosition(const vec3 &position) noexcept
	{
		__pos = position;
	}

	void PositionableLightComponent::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	void PositionableLightComponent::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	void PositionableLightComponent::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	void PositionableLightComponent::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	void PositionableLightComponent::adjustPosition(const vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	void PositionableLightComponent::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	void PositionableLightComponent::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	void PositionableLightComponent::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	void PositionableLightComponent::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}
}
