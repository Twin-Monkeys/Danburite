#pragma once

#include "LightUniformDeployable.h"

namespace Danburite
{
	class PositionableLightComponent abstract : virtual public LightUniformDeployable
	{
	private:
		glm::vec3 __pos = { 0.f, 0.f, 0.f };

	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		constexpr const glm::vec3 &getPosition() const noexcept;
		constexpr void setPosition(const glm::vec3 &position) noexcept;
		constexpr void setPosition(const float xPos, const float yPos, const float zPos) noexcept;
		constexpr void setPositionX(const float xPos) noexcept;
		constexpr void setPositionY(const float yPos) noexcept;
		constexpr void setPositionZ(const float zPos) noexcept;
		constexpr void adjustPosition(const glm::vec3 &delta) noexcept;
		constexpr void adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept;
		constexpr void adjustPositionX(const float xDelta) noexcept;
		constexpr void adjustPositionY(const float yDelta) noexcept;
		constexpr void adjustPositionZ(const float zDelta) noexcept;

		virtual ~PositionableLightComponent() = default;
	};

	constexpr const glm::vec3 &PositionableLightComponent::getPosition() const noexcept
	{
		return __pos;
	}

	constexpr void PositionableLightComponent::setPosition(const glm::vec3 &position) noexcept
	{
		__pos = position;
	}

	constexpr void PositionableLightComponent::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	constexpr void PositionableLightComponent::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	constexpr void PositionableLightComponent::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	constexpr void PositionableLightComponent::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	constexpr void PositionableLightComponent::adjustPosition(const glm::vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	constexpr void PositionableLightComponent::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	constexpr void PositionableLightComponent::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	constexpr void PositionableLightComponent::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	constexpr void PositionableLightComponent::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}
}