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
		constexpr void setPosition(const glm::vec3 &position) noexcept;
		constexpr void setPosition(const float x, const float y, const float z) noexcept;

		void setDirection(const glm::vec3 &direction) noexcept;
		void setDirection(const float x, const float y, const float z) noexcept;

		void setUp(const glm::vec3 &up) noexcept;
		void setUp(const float x, const float y, const float z) noexcept;

		constexpr void setViewingVolume(
			const float xLeft, const float xRight,
			const float yBottom, const float yTop,
			const float zNear, const float zFar) noexcept;
	};

	constexpr void DepthBakingCamera::setPosition(const glm::vec3 &position) noexcept
	{
		__pos = position;
	}

	constexpr void DepthBakingCamera::setPosition(const float x, const float y, const float z) noexcept
	{
		setPosition({ x, y, z });
	}

	constexpr void DepthBakingCamera::setViewingVolume(
		const float xLeft, const float xRight,
		const float yBottom, const float yTop,
		const float zNear, const float zFar) noexcept
	{
		__viewingVolumeLeft = xLeft;
		__viewingVolumeRight = xRight;
		__viewingVolumeBottom = yBottom;
		__viewingVolumeTop = yTop;
		__viewingVolumeNear = zNear;
		__viewingVolumeFar = zFar;
	}
}
