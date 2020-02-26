#pragma once

#include "Camera.h"
#include "Constant.h"

namespace Danburite
{
	class SimpleCamera : public Camera
	{
	private:
		float __maxPitch = Constant::Camera::MAX_PITCH;
		float __maxFov = Constant::Camera::MAX_FOV;
		float __minFov = Constant::Camera::MIN_FOV;

		glm::vec3 __pos = { 0.f, 0.f, 0.f };
		glm::vec3 __forward = { 0.f, 0.f, -1.f };
		glm::vec3 __horizontal = { 1.f, 0.f, 0.f };

		float __pitch = 0.f;
		glm::vec3 __vertical = { 0.f, 1.f, 0.f };
		const glm::vec3 __up = { 0.f, 1.f, 0.f };

		float __fov = Constant::Camera::FOV;
		float __aspectRatio = 1.f;

		float __zNear = Constant::Camera::Z_NEAR;
		float __zFar = Constant::Camera::Z_FAR;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept override;
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept override;
		virtual void _onDeploy(ObjectGL::UniformSetter &target) noexcept override;

	public:
		SimpleCamera() noexcept;

		constexpr const glm::vec3 &getPosition() const noexcept;
		constexpr const glm::vec3 &getForward() const noexcept;
		constexpr const glm::vec3 &getHorizontal() const noexcept;
		constexpr const glm::vec3 &getVertical() const noexcept;

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

		constexpr void moveForward(const float delta) noexcept;
		constexpr void moveHorizontal(const float delta) noexcept;
		constexpr void moveVertical(const float delta) noexcept;

		void pitch(const float angle) noexcept;
		void yaw(const float angle) noexcept;

		// projection
		constexpr void setFov(const float fov) noexcept;
		constexpr void resetFov() noexcept;
		constexpr void adjustFov(const float delta) noexcept;

		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(const int width, const int height) noexcept;

		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

		// bounds
		constexpr void setMaxPitch(const float maxPitch) noexcept;
		constexpr void setMaxFov(const float maxFov) noexcept;
		constexpr void setMinFov(const float minFov) noexcept;

		virtual ~SimpleCamera() = default;
	};

	constexpr const glm::vec3 &SimpleCamera::getPosition() const noexcept
	{
		return __pos;
	}

	constexpr const glm::vec3& SimpleCamera::getForward() const noexcept
	{
		return __forward;
	}

	constexpr const glm::vec3 &SimpleCamera::getHorizontal() const noexcept
	{
		return __horizontal;
	}

	constexpr const glm::vec3 &SimpleCamera::getVertical() const noexcept
	{
		return __vertical;
	}

	constexpr void SimpleCamera::setPosition(const glm::vec3 &position) noexcept
	{
		__pos = position;
	}

	constexpr void SimpleCamera::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	constexpr void SimpleCamera::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	constexpr void SimpleCamera::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	constexpr void SimpleCamera::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	constexpr void SimpleCamera::adjustPosition(const glm::vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	constexpr void SimpleCamera::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	constexpr void SimpleCamera::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	constexpr void SimpleCamera::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	constexpr void SimpleCamera::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}

	constexpr void SimpleCamera::moveForward(const float delta) noexcept
	{
		adjustPosition(__forward * delta);
	}

	constexpr void SimpleCamera::moveHorizontal(const float delta) noexcept
	{
		adjustPosition(__horizontal * delta);
	}

	constexpr void SimpleCamera::moveVertical(const float delta) noexcept
	{
		adjustPosition(__vertical * delta);
	}

	constexpr void SimpleCamera::setFov(const float fov) noexcept
	{
		float validFov = fov;

		if (validFov > __maxFov)
			validFov = __maxFov;
		else if (validFov < __minFov)
			validFov = __minFov;

		__fov = validFov;
	}

	constexpr void SimpleCamera::resetFov() noexcept
	{
		setFov(Constant::Camera::FOV);
	}

	constexpr void SimpleCamera::adjustFov(const float delta) noexcept
	{
		setFov(__fov + delta);
	}

	constexpr void SimpleCamera::setAspectRatio(const float ratio) noexcept
	{
		__aspectRatio = ratio;
	}

	constexpr void SimpleCamera::setAspectRatio(const int width, const int height) noexcept
	{
		setAspectRatio(float(width) / float(height));
	}

	constexpr void SimpleCamera::setNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	constexpr void SimpleCamera::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}

	constexpr void SimpleCamera::setMaxPitch(const float maxPitch) noexcept
	{
		__maxPitch = maxPitch;
	}

	constexpr void SimpleCamera::setMaxFov(const float maxFov) noexcept
	{
		__maxFov = maxFov;
	}

	constexpr void SimpleCamera::setMinFov(const float minFov) noexcept
	{
		__minFov = minFov;
	}
}
