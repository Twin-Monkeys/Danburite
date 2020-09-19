#pragma once

#include "Quaternion.h"
#include <glm/gtc/constants.hpp>
#include "Constant.h"

namespace Danburite
{
	class Transform
	{
	private:
		glm::vec3 __position		{ 0.f, 0.f, 0.f };
		Quaternion __rotation;
		glm::vec3 __scale			{ 1.f, 1.f, 1.f };

		glm::mat4 __translationMat	{ 1.f };
		glm::mat4 __scaleMat		{ 1.f };
		glm::mat4 __rotationMat		{ 1.f };
		glm::mat4 __modelMat		{ 1.f };

	public:
		Transform() = default;

		// position
		constexpr const glm::vec3 &getPosition() const noexcept;
		constexpr Transform &setPosition(const glm::vec3 &position) noexcept;
		constexpr Transform &setPosition(const float x, const float y, const float z) noexcept;
		constexpr Transform &adjustPosition(const glm::vec3 &delta) noexcept;
		constexpr Transform &adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept;

		// scale
		constexpr const glm::vec3 &getScale() const noexcept;
		constexpr Transform &setScale(const float uniformScale) noexcept;
		constexpr Transform &setScale(const glm::vec3 &scale) noexcept;
		constexpr Transform &setScale(const float x, const float y, const float z) noexcept;
		constexpr Transform &adjustScale(const float uniformDelta) noexcept;
		constexpr Transform &adjustScale(const glm::vec3 &delta) noexcept;
		constexpr Transform &adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept;

		// rotation
		constexpr Quaternion &getRotation() noexcept;
		constexpr const Quaternion &getRotation() const noexcept;
		

		// util
		Transform &moveForward(const float delta) noexcept;
		Transform &moveHorizontal(const float delta) noexcept;
		Transform &moveVertical(const float delta) noexcept;
		Transform &orient(const glm::vec3 &forward, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;
		Transform &lookAt(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;
		Transform &orbit(const float angle, const glm::vec3 &pivot, const glm::vec3 &axis, const bool angleRotation = true) noexcept;

		constexpr const glm::vec4 &getForward() const noexcept;
		constexpr const glm::vec4 &getHorizontal() const noexcept;
		constexpr const glm::vec4 &getVertical() const noexcept;

		constexpr const glm::mat4 &getMatrix() const noexcept;

		constexpr Transform &operator=(const Transform &transform) = default;

		void updateMatrix() noexcept;

		virtual ~Transform() = default;

		static glm::mat4 calcMatrix(const glm::vec3 &position, const Quaternion &rotation, const glm::vec3 &scale) noexcept;
	};

	constexpr const glm::vec3& Transform::getPosition() const noexcept
	{
		return __position;
	}

	constexpr Transform &Transform::setPosition(const glm::vec3 &position) noexcept
	{
		return setPosition(position.x, position.y, position.z);
	}

	constexpr Transform &Transform::setPosition(const float x, const float y, const float z) noexcept
	{
		__position.x = x;
		__position.y = y;
		__position.z = z;
		return *this;
	}

	constexpr Transform &Transform::adjustPosition(const glm::vec3 &delta) noexcept
	{
		return adjustPosition(delta.x, delta.y, delta.z);
	}
	
	constexpr Transform &Transform::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		return setPosition(__position.x + xDelta, __position.y + yDelta, __position.z + zDelta);
	}

	constexpr const glm::vec3 &Transform::getScale() const noexcept
	{
		return __scale;
	}

	constexpr Transform &Transform::setScale(const float uniformScale) noexcept
	{
		return setScale(uniformScale, uniformScale, uniformScale);
	}

	constexpr Transform &Transform::setScale(const glm::vec3 &scale) noexcept
	{
		return setScale(scale.x, scale.y, scale.z);
	}

	constexpr Transform &Transform::setScale(const float x, const float y, const float z) noexcept
	{
		__scale.x = x;
		__scale.y = y;
		__scale.z = z;
		clamp(__scale, Constant::Transform::MIN_SCALE, Constant::Transform::MAX_SCALE);

		return *this;
	}

	constexpr Transform &Transform::adjustScale(const float uniformDelta) noexcept
	{
		return adjustScale(uniformDelta, uniformDelta, uniformDelta);
	}

	constexpr Transform &Transform::adjustScale(const glm::vec3 &delta) noexcept
	{
		return adjustScale(delta.x, delta.y, delta.z);
	}

	constexpr Transform &Transform::adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		return setScale(__scale.x + xDelta, __scale.y + yDelta, __scale.z + zDelta);
	}

	constexpr Quaternion &Transform::getRotation() noexcept
	{
		return __rotation;
	}

	constexpr const Quaternion &Transform::getRotation() const noexcept
	{
		return __rotation;
	}

	constexpr const glm::vec4 &Transform::getForward() const noexcept
	{
		return __rotationMat[2];
	}

	constexpr const glm::vec4 &Transform::getHorizontal() const noexcept
	{
		return __rotationMat[0];
	}

	constexpr const glm::vec4 &Transform::getVertical() const noexcept
	{
		return __rotationMat[1];
	}

	constexpr const glm::mat4 &Transform::getMatrix() const noexcept
	{
		return __modelMat;
	}
}
