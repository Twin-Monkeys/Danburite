#pragma once

#include <utility>
#include "UniformDeployable.h"

namespace Danburite
{
	class Transform
	{
	private:
		glm::vec3 __pos = { 0.f, 0.f, 0.f };
		glm::vec3 __scale = { 1.f, 1.f, 1.f };
		std::pair<float, glm::vec3> __rotation = { 0.f, { 0.f, 1.f, 0.f } };

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

		void orbit(const float angle, const glm::vec3& pivot, const glm::vec3 &axis) noexcept;

		const glm::vec3 &getScale() const noexcept;

		void setScale(const float scale) noexcept;
		void setScale(const glm::vec3 &scale) noexcept;
		void setScale(const float xScale, const float yScale, const float zScale) noexcept;
		void setScaleX(const float xScale) noexcept;
		void setScaleY(const float yScale) noexcept;
		void setScaleZ(const float zScale) noexcept;

		void adjustScale(const glm::vec3 &delta) noexcept;
		void adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept;
		void adjustScaleX(const float xDelta) noexcept;
		void adjustScaleY(const float yDelta) noexcept;
		void adjustScaleZ(const float zDelta) noexcept;

		const std::pair<float, glm::vec3> &getRotation() const noexcept;
		void setRotationAngle(const float angle) noexcept;
		void setRotationAxis(const glm::vec3 &axis) noexcept;
		void setRotation(const float angle, const glm::vec3 &axis) noexcept;
		void adjustRotationAngle(const float delta) noexcept;

		void calcModelMatrix(const glm::mat4 &parentModelMat, glm::mat4 &retVal) noexcept;

		virtual ~Transform() = default;
	};
}
