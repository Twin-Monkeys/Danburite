#pragma once

#include "Updatable.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Constant.h"

namespace Danburite
{
	class Transform : public Updatable
	{
	private:
		glm::vec3 __position		{ 0.f, 0.f, 0.f };
		glm::vec3 __scale			{ 1.f, 1.f, 1.f };
		glm::vec3 __rotation		{ 0.f, 0.f, 0.f };

		glm::mat4 __translationMat	{ 1.f };
		glm::mat4 __scaleMat		{ 1.f };
		glm::mat4 __rotationMat		{ 1.f };
		glm::mat4 __modelMat		{ 1.f };

		static constexpr void __adjustAngleToPeriod(glm::vec3 &angle) noexcept;

	protected:
		virtual void _onUpdateTranslation(glm::mat4 &translationMat) const noexcept;
		virtual void _onUpdateScale(glm::mat4 &ScaleMat) const noexcept;
		virtual void _onUpdateRotation(glm::mat4 &RotationMat) const noexcept;

	public:
		// position
		constexpr const glm::vec3 &getPosition() const noexcept;
		constexpr void setPosition(const glm::vec3 &position) noexcept;
		constexpr void setPosition(const float x, const float y, const float z) noexcept;
		constexpr void adjustPosition(const glm::vec3 &delta) noexcept;
		constexpr void adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept;

		// scale
		constexpr const glm::vec3 &getScale() const noexcept;
		constexpr void setScale(const float uniformScale) noexcept;
		constexpr void setScale(const glm::vec3 &scale) noexcept;
		constexpr void setScale(const float x, const float y, const float z) noexcept;
		constexpr void adjustScale(const float uniformDelta) noexcept;
		constexpr void adjustScale(const glm::vec3 &delta) noexcept;
		constexpr void adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept;

		// rotation
		constexpr const glm::vec3 &getRotation() const noexcept;
		constexpr void setRotation(const glm::vec3 &rotation) noexcept;
		constexpr void setRotation(const float pitch, const float yaw, const float roll) noexcept;
		constexpr void adjustRotation(const glm::vec3 &delta) noexcept;
		constexpr void adjustRotation(const float pitch, const float yaw, const float roll) noexcept;

		// util
		void moveForward(const float delta) noexcept;
		void moveHorizontal(const float delta) noexcept;
		void moveVertical(const float delta) noexcept;
		void orbit(const float angle, const glm::vec3& pivot, const glm::vec3 &axis, const bool angleRotation = true) noexcept;

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

	constexpr void Transform::__adjustAngleToPeriod(glm::vec3 &angle) noexcept
	{
		constexpr auto adjAngle = [](float& angle)
		{
			if (angle < -glm::pi<float>())
				angle += glm::two_pi<float>();

			else if (angle > glm::pi<float>())
				angle -= glm::two_pi<float>();
		};

		adjAngle(angle.x);
		adjAngle(angle.y);
		adjAngle(angle.z);
	}

	constexpr const glm::vec3& Transform::getPosition() const noexcept
	{
		return __position;
	}

	constexpr void Transform::setPosition(const glm::vec3 &position) noexcept
	{
		setPosition(position.x, position.y, position.z);
	}

	constexpr void Transform::setPosition(const float x, const float y, const float z) noexcept
	{
		__position.x = x;
		__position.y = y;
		__position.z = z;
	}

	constexpr void Transform::adjustPosition(const glm::vec3 &delta) noexcept
	{
		adjustPosition(delta.x, delta.y, delta.z);
	}
	
	constexpr void Transform::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		__position.x += xDelta;
		__position.y += yDelta;
		__position.z += zDelta;
	}

	constexpr const glm::vec3 &Transform::getScale() const noexcept
	{
		return __scale;
	}

	constexpr void Transform::setScale(const float uniformScale) noexcept
	{
		setScale(uniformScale, uniformScale, uniformScale);
	}

	constexpr void Transform::setScale(const glm::vec3 &scale) noexcept
	{
		setScale(scale.x, scale.y, scale.z);
	}

	constexpr void Transform::setScale(const float x, const float y, const float z) noexcept
	{
		__scale.x = x;
		__scale.y = y;
		__scale.z = z;

		clamp(__scale, Constant::Transform::MIN_SCALE, Constant::Transform::MAX_SCALE);
	}

	constexpr void Transform::adjustScale(const float uniformDelta) noexcept
	{
		adjustScale(uniformDelta, uniformDelta, uniformDelta);
	}

	constexpr void Transform::adjustScale(const glm::vec3 &delta) noexcept
	{
		adjustScale(delta.x, delta.y, delta.z);
	}

	constexpr void Transform::adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		__scale.x += xDelta;
		__scale.y += yDelta;
		__scale.z += zDelta;

		clamp(__scale, Constant::Transform::MIN_SCALE, Constant::Transform::MAX_SCALE);
	}

	constexpr const glm::vec3 &Transform::getRotation() const noexcept
	{
		return __rotation;
	}

	constexpr void Transform::setRotation(const glm::vec3 &rotation) noexcept
	{
		setRotation(rotation.x, rotation.y, rotation.z);
	}

	constexpr void Transform::setRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		__rotation.x = pitch;
		__rotation.y = yaw;
		__rotation.z = roll;

		__adjustAngleToPeriod(__rotation);
	}

	constexpr void Transform::adjustRotation(const glm::vec3 &delta) noexcept
	{
		adjustRotation(delta.x, delta.y, delta.z);
	}

	constexpr void Transform::adjustRotation(const float pitch, const float yaw, const float roll) noexcept
	{
		__rotation.x += pitch;
		__rotation.y += yaw;
		__rotation.z += roll;

		__adjustAngleToPeriod(__rotation);
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
