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

		const glm::vec3 &getPosition() const noexcept;
		const glm::vec3 &getForward() const noexcept;
		const glm::vec3 &getHorizontal() const noexcept;
		const glm::vec3 &getVertical() const noexcept;

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

		void moveForward(const float delta) noexcept;
		void moveHorizontal(const float delta) noexcept;
		void moveVertical(const float delta) noexcept;

		void pitch(const float angle) noexcept;
		void yaw(const float angle) noexcept;

		// projection
		void setFov(const float fov) noexcept;
		void resetFov() noexcept;
		void adjustFov(const float delta) noexcept;

		void setAspectRatio(const float ratio) noexcept;
		void setAspectRatio(const int width, const int height) noexcept;

		void setNear(const float zNear) noexcept;
		void setFar(const float zFar) noexcept;

		// bounds
		void setMaxPitch(const float maxPitch) noexcept;
		void setMaxFov(const float maxFov) noexcept;
		void setMinFov(const float minFov) noexcept;

		virtual ~SimpleCamera() = default;
	};
}
