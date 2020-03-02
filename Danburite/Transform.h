#pragma once

#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Danburite
{
	class Transform
	{
	private:
		glm::vec3 __pos = { 0.f, 0.f, 0.f };
		glm::vec3 __scale = { 1.f, 1.f, 1.f };
		std::pair<float, glm::vec3> __rotation = { 0.f, { 0.f, 1.f, 0.f } };

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

		void orbit(const float angle, const glm::vec3& pivot, const glm::vec3 &axis) noexcept;

		constexpr const glm::vec3 &getScale() const noexcept;

		constexpr void setScale(const float scale) noexcept;
		constexpr void setScale(const glm::vec3 &scale) noexcept;
		constexpr void setScale(const float xScale, const float yScale, const float zScale) noexcept;
		constexpr void setScaleX(const float xScale) noexcept;
		constexpr void setScaleY(const float yScale) noexcept;
		constexpr void setScaleZ(const float zScale) noexcept;

		constexpr void adjustScale(const glm::vec3 &delta) noexcept;
		constexpr void adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept;
		constexpr void adjustScaleX(const float xDelta) noexcept;
		constexpr void adjustScaleY(const float yDelta) noexcept;
		constexpr void adjustScaleZ(const float zDelta) noexcept;

		constexpr const std::pair<float, glm::vec3> &getRotation() const noexcept;

		constexpr void setRotationAngle(const float angle) noexcept;
		void setRotationAxis(const glm::vec3 &axis) noexcept;
		void setRotation(const float angle, const glm::vec3 &axis) noexcept;
		constexpr void adjustRotationAngle(const float delta) noexcept;

		void calcModelMatrix(const glm::mat4 &parentModelMat, glm::mat4 &retVal) noexcept;

		virtual ~Transform() = default;
	};

	constexpr const glm::vec3 &Transform::getPosition() const noexcept
	{
		return __pos;
	}

	constexpr void Transform::setPosition(const glm::vec3 &position) noexcept
	{
		__pos = position;
	}

	constexpr void Transform::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	constexpr void Transform::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	constexpr void Transform::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	constexpr void Transform::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	constexpr void Transform::adjustPosition(const glm::vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	constexpr void Transform::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	constexpr void Transform::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	constexpr void Transform::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	constexpr void Transform::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}

	constexpr const glm::vec3 &Transform::getScale() const noexcept
	{
		return __scale;
	}

	constexpr void Transform::setScale(const float scale) noexcept
	{
		setScale(scale, scale, scale);
	}

	constexpr void Transform::setScale(const glm::vec3 &scale) noexcept
	{
		__scale = scale;
	}

	constexpr void Transform::setScale(const float xScale, const float yScale, const float zScale) noexcept
	{
		setScale({ xScale, yScale, zScale });
	}

	constexpr void Transform::setScaleX(const float xScale) noexcept
	{
		setScale({ xScale, __scale.y, __scale.z });
	}

	constexpr void Transform::setScaleY(const float yScale) noexcept
	{
		setScale({ __scale.x, yScale, __scale.z });
	}

	constexpr void Transform::setScaleZ(const float zScale) noexcept
	{
		setScale({ __scale.x, __scale.y, zScale });
	}

	constexpr void Transform::adjustScale(const glm::vec3 &delta) noexcept
	{
		setScale(__scale + delta);
	}

	constexpr void Transform::adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustScale({ xDelta, yDelta, zDelta });
	}

	constexpr void Transform::adjustScaleX(const float xDelta) noexcept
	{
		adjustScale({ xDelta, 0.f, 0.f });
	}

	constexpr void Transform::adjustScaleY(const float yDelta) noexcept
	{
		adjustScale({ 0.f, yDelta, 0.f });
	}

	constexpr void Transform::adjustScaleZ(const float zDelta) noexcept
	{
		adjustScale({ 0.f, 0.f, zDelta });
	}

	constexpr const std::pair<float, glm::vec3> &Transform::getRotation() const noexcept
	{
		return __rotation;
	}

	constexpr void Transform::setRotationAngle(const float angle) noexcept
	{
		constexpr float TWO_PI = glm::two_pi<float>();
		float validAngle = angle;

		if (validAngle > TWO_PI)
			validAngle -= TWO_PI;
		else if (validAngle < -TWO_PI)
			validAngle += TWO_PI;

		__rotation.first = validAngle;
	}

	constexpr void Transform::adjustRotationAngle(const float delta) noexcept
	{
		setRotationAngle(__rotation.first + delta);
	}
}
