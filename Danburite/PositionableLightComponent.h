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
		const glm::vec3 &getPosition() const noexcept;
		void setPosition(const glm::vec3 &position) noexcept;
		void setPosition(const float xPos, const float yPos, const float zPos) noexcept;
		void setPositionX(const float xPos) noexcept;
		void setPositionY(const float yPos) noexcept;
		void setPositionZ(const float zPos) noexcept;
		void adjustPosition(const glm::vec3 &delta) noexcept;
		void adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept;
		void adjustPositionX(const float xDelta) noexcept;
		void adjustPositionY(const float yDelta) noexcept;
		void adjustPositionZ(const float zDelta) noexcept;

		virtual ~PositionableLightComponent() = default;
	};
}