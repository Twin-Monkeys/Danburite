#pragma once

#include "TransformComponent.h"
#include <glm/gtc/constants.hpp>
#include "Constant.h"

namespace Danburite
{
	class Transform
	{
	private:
		TransformComponent __component;

		glm::mat4 __translationMat	{ 1.f };
		glm::mat4 __scaleMat		{ 1.f };
		glm::mat4 __rotationMat		{ 1.f };
		glm::mat4 __modelMat		{ 1.f };

	protected:
		virtual void _onUpdateTranslationMatrix(glm::mat4 &translationMat) noexcept;
		virtual void _onUpdateScaleMatrix(glm::mat4 &scaleMat) noexcept;
		virtual void _onUpdateRotationMatrix(glm::mat4 &rotationMat) noexcept;

	public:
		Transform() = default;
		constexpr Transform(const TransformComponent &component) noexcept;

		constexpr const TransformComponent &getComponent() const noexcept;
		constexpr Transform &setComponent(const TransformComponent &component) noexcept;

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
		constexpr const Quaternion &getRotation() const noexcept;
		Transform &setRotation(const glm::vec3 &eularAngles) noexcept;
		Transform &setRotation(const float pitch, const float yaw, const float roll) noexcept;
		Transform &setRotation(const Quaternion &rotation) noexcept;

		Transform &rotateGlobal(const glm::vec3 &eulerAngles) noexcept;
		Transform &rotateGlobal(const float pitch, const float yaw, const float roll) noexcept;
		Transform &rotateGlobal(const float angle, const glm::vec3 &axis) noexcept;

		Transform &rotateLocal(const glm::vec3 &eulerAngles) noexcept;
		Transform &rotateLocal(const float pitch, const float yaw, const float roll) noexcept;
		Transform &rotateFPS(const float pitch, const float yaw, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		// util
		Transform &moveForward(const float delta) noexcept;
		Transform &moveHorizontal(const float delta) noexcept;
		Transform &moveVertical(const float delta) noexcept;
		Transform &lookAt(const glm::vec3 &forward, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;
		Transform &orbit(const float angle, const glm::vec3 &pivot, const glm::vec3 &axis, const bool angleRotation = true) noexcept;

		constexpr const glm::vec4 &getForward() const noexcept;
		constexpr const glm::vec4 &getHorizontal() const noexcept;
		constexpr const glm::vec4 &getVertical() const noexcept;

		constexpr const glm::mat4 &getTranslationMatrix() const noexcept;
		constexpr const glm::mat4 &getScaleMatrix() const noexcept;
		constexpr const glm::mat4 &getRotationMatrix() const noexcept;
		constexpr const glm::mat4 &getModelMatrix() const noexcept;

		constexpr Transform &operator=(const Transform &transform) = default;
		constexpr Transform &operator=(const TransformComponent &component) noexcept;

		virtual void updateMatrix(const float deltaTime) noexcept;

		virtual ~Transform() = default;
	};

	constexpr Transform::Transform(const TransformComponent &component) noexcept :
		__component(component)
	{}

	constexpr const TransformComponent &Transform::getComponent() const noexcept
	{
		return __component;
	}

	constexpr Transform &Transform::setComponent(const TransformComponent &component) noexcept
	{
		__component = component;
		return *this;
	}

	constexpr const glm::vec3& Transform::getPosition() const noexcept
	{
		return __component.position;
	}

	constexpr Transform &Transform::setPosition(const glm::vec3 &position) noexcept
	{
		return setPosition(position.x, position.y, position.z);
	}

	constexpr Transform &Transform::setPosition(const float x, const float y, const float z) noexcept
	{
		__component.position.x = x;
		__component.position.y = y;
		__component.position.z = z;
		return *this;
	}

	constexpr Transform &Transform::adjustPosition(const glm::vec3 &delta) noexcept
	{
		return adjustPosition(delta.x, delta.y, delta.z);
	}
	
	constexpr Transform &Transform::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		__component.position.x += xDelta;
		__component.position.y += yDelta;
		__component.position.z += zDelta;
		return *this;
	}

	constexpr const glm::vec3 &Transform::getScale() const noexcept
	{
		return __component.scale;
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
		__component.scale.x = x;
		__component.scale.y = y;
		__component.scale.z = z;
		clamp(__component.scale, Constant::Transform::MIN_SCALE, Constant::Transform::MAX_SCALE);

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
		return setScale(
			__component.scale.x + xDelta,
			__component.scale.y + yDelta,
			__component.scale.z + zDelta);
	}

	constexpr const Quaternion &Transform::getRotation() const noexcept
	{
		return __component.rotation;
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

	constexpr const glm::mat4 &Transform::getTranslationMatrix() const noexcept
	{
		return __translationMat;
	}

	constexpr const glm::mat4 &Transform::getScaleMatrix() const noexcept
	{
		return __scaleMat;
	}

	constexpr const glm::mat4 &Transform::getRotationMatrix() const noexcept
	{
		return __rotationMat;
	}

	constexpr const glm::mat4 &Transform::getModelMatrix() const noexcept
	{
		return __modelMat;
	}

	constexpr Transform &Transform::operator=(const TransformComponent &component) noexcept
	{
		return setComponent(component);
	}
}
