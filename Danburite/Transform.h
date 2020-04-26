#pragma once

#include "Updatable.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Constant.h"
#include "Quaternion.h"

namespace Danburite
{
	class Transform : public Updatable
	{
	private:
		glm::vec3 __position		{ 0.f, 0.f, 0.f };
		glm::vec3 __scale			{ 1.f, 1.f, 1.f };
		Quaternion __rotation		{ 0.f, 0.f, 0.f };

		glm::mat4 __translationMat	{ 1.f };
		glm::mat4 __scaleMat		{ 1.f };
		glm::mat4 __rotationMat		{ 1.f };
		glm::mat4 __modelMat		{ 1.f };

	protected:
		virtual void _onUpdateTranslationMatrix(glm::mat4 &translationMat) const noexcept;
		virtual void _onUpdateScaleMatrix(glm::mat4 &scaleMat) const noexcept;
		virtual void _onUpdateRotationMatrix(glm::mat4 &rotationMat) const noexcept;

	public:
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
		Transform &rotateLocal(const glm::vec3 &eulerAngles) noexcept;
		Transform &rotateLocal(const float pitch, const float yaw, const float roll) noexcept;
		Transform &rotateFPS(const float pitch, const float yaw, const glm::vec3 &referenceUp = { 0.f, 1.f, 0.f }) noexcept;

		// util
		Transform &moveForward(const float delta) noexcept;
		Transform &moveHorizontal(const float delta) noexcept;
		Transform &moveVertical(const float delta) noexcept;
		Transform &orbit(const float angle, const glm::vec3& pivot, const glm::vec3 &axis, const bool angleRotation = true) noexcept;

		constexpr const glm::vec4 &getForward() const noexcept;
		constexpr const glm::vec4 &getHorizontal() const noexcept;
		constexpr const glm::vec4 &getVertical() const noexcept;

		constexpr const glm::mat4 &getTranslationMatrix() const noexcept;
		constexpr const glm::mat4 &getScaleMatrix() const noexcept;
		constexpr const glm::mat4 &getRotationMatrix() const noexcept;
		constexpr const glm::mat4 &getModelMatrix() const noexcept;

		virtual void update() noexcept override;

		virtual ~Transform() = default;
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
		__position.x += xDelta;
		__position.y += yDelta;
		__position.z += zDelta;
		return *this;
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
		__scale.x += xDelta;
		__scale.y += yDelta;
		__scale.z += zDelta;
		clamp(__scale, Constant::Transform::MIN_SCALE, Constant::Transform::MAX_SCALE);

		return *this;
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
}
