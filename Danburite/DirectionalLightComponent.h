#pragma once

#include "LightUniformDeployable.h"

namespace Danburite
{
	class DirectionalLightComponent abstract : virtual public LightUniformDeployable
	{
	private:
		glm::vec3 __direction = { 0.f, -1.f, 0.f };

	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		constexpr const glm::vec3 &getDirection() const noexcept;
		void setDirection(const glm::vec3 &direction) noexcept;
		void setDirection(const float x, const float y, const float z) noexcept;

		virtual ~DirectionalLightComponent() = default;
	};

	constexpr const glm::vec3 &DirectionalLightComponent::getDirection() const noexcept
	{
		return __direction;
	}
}