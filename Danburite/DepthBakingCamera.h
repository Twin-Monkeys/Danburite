#pragma once

#include "Camera.h"

namespace Danburite
{
	class DepthBakingCamera : public Camera
	{
	private:
		glm::vec3 __pos = { 0.f, 0.f, 0.f };
		glm::vec3 __direction = { 0.f, 0.f, -1.f };

		glm::vec3 __up = { 0.f, 1.f, 0.f };

		float __viewingVolumeLeft = -10.f;
		float __viewingVolumeRight = 10.f;
		float __viewingVolumeBottom = -10.f;
		float __viewingVolumeTop = 10.f;
		float __viewingVolumeNear = 1.f;
		float __viewingVolumeFar = 1000.f;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept override;
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept override;

	public:
		void setPosition(const glm::vec3 &position) noexcept;
		void setPosition(const float x, const float y, const float z) noexcept;

		void setDirection(const glm::vec3 &direction) noexcept;
		void setDirection(const float x, const float y, const float z) noexcept;

		void setUp(const glm::vec3 &up) noexcept;
		void setUp(const float x, const float y, const float z) noexcept;

		void setViewingVolume(
			const float left, const float right,
			const float bottom, const float top,
			const float near, const float far) noexcept;
	};
}
