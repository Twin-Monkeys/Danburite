#pragma once

#include "Camera.h"
#include "Constant.h"

namespace Danburite
{
	class OrthoCamera : public Camera
	{
	private:
		float __maxPitch = Constant::Camera::MAX_PITCH;

		glm::vec3 __pos = { 0.f, 0.f, 0.f };
		glm::vec3 __forward = { 0.f, 0.f, -1.f };
		glm::vec3 __horizontal = { 1.f, 0.f, 0.f };

		float __pitch = 0.f;
		glm::vec3 __vertical = { 0.f, 1.f, 0.f };
		const glm::vec3 __up = { 0.f, 1.f, 0.f };

		float __xLeft = Constant::Camera::DEFAULT_X_LEFT;
		float __xRight = Constant::Camera::DEFAULT_X_RIGHT;
		float __yBottom = Constant::Camera::DEFAULT_Y_BOTTOM;
		float __yTop = Constant::Camera::DEFAULT_Y_TOP;
		float __zNear = Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar = Constant::Camera::DEFAULT_Z_FAR;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept override;
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept override;
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) noexcept override;

	public:
		OrthoCamera() noexcept;

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
		constexpr void setLeft(const float xLeft) noexcept;
		constexpr void setRight(const float xRight) noexcept;
		constexpr void setBottom(const float yBottom) noexcept;
		constexpr void setTop(const float yTop) noexcept;
		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

		constexpr void setOrtho(
			const float xLeft, const float xRight,
			const float yBottom, const float yTop,
			const float zNear, const float zFar) noexcept;

		// bounds
		constexpr void setMaxPitch(const float maxPitch) noexcept;

		virtual ~OrthoCamera() = default;
	};

	constexpr const glm::vec3 &OrthoCamera::getPosition() const noexcept
	{
		return __pos;
	}

	constexpr const glm::vec3 &OrthoCamera::getForward() const noexcept
	{
		return __forward;
	}

	constexpr const glm::vec3 &OrthoCamera::getHorizontal() const noexcept
	{
		return __horizontal;
	}

	constexpr const glm::vec3 &OrthoCamera::getVertical() const noexcept
	{
		return __vertical;
	}

	constexpr void OrthoCamera::setPosition(const glm::vec3 &position) noexcept
	{
		__pos = position;
	}

	constexpr void OrthoCamera::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	constexpr void OrthoCamera::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	constexpr void OrthoCamera::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	constexpr void OrthoCamera::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	constexpr void OrthoCamera::adjustPosition(const glm::vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	constexpr void OrthoCamera::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	constexpr void OrthoCamera::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	constexpr void OrthoCamera::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	constexpr void OrthoCamera::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}

	constexpr void OrthoCamera::moveForward(const float delta) noexcept
	{
		adjustPosition(__forward * delta);
	}

	constexpr void OrthoCamera::moveHorizontal(const float delta) noexcept
	{
		adjustPosition(__horizontal * delta);
	}

	constexpr void OrthoCamera::moveVertical(const float delta) noexcept
	{
		adjustPosition(__vertical * delta);
	}

	constexpr void OrthoCamera::setLeft(const float xLeft) noexcept
	{
		__xLeft = xLeft;
	}

	constexpr void OrthoCamera::setRight(const float xRight) noexcept
	{
		__xRight = xRight;
	}

	constexpr void OrthoCamera::setBottom(const float yBottom) noexcept
	{
		__yBottom = yBottom;
	}

	constexpr void OrthoCamera::setTop(const float yTop) noexcept
	{
		__yTop = yTop;
	}

	constexpr void OrthoCamera::setNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	constexpr void OrthoCamera::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}

	constexpr void OrthoCamera::setOrtho(
		const float xLeft, const float xRight,
		const float yBottom, const float yTop,
		const float zNear, const float zFar) noexcept
	{
		__xLeft = xLeft;
		__xRight = xRight;
		__yBottom = yBottom;
		__yTop = yTop;
		__zNear = zNear;
		__zFar = zFar;
	}

	constexpr void OrthoCamera::setMaxPitch(const float maxPitch) noexcept
	{
		__maxPitch = maxPitch;
	}
}
