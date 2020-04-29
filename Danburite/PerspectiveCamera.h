#pragma once

#include "TransformableCamera.h"
#include "Constant.h"

namespace Danburite
{
	class PerspectiveCamera : public TransformableCamera
	{
	private:
		float __maxFov = Constant::Camera::MAX_FOV;
		float __minFov = Constant::Camera::MIN_FOV;
		float __fov = Constant::Camera::DEFAULT_FOV;

		float __aspectRatio = Constant::Camera::DEFAULT_ASPECT_RATIO;

		float __zNear = Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar = Constant::Camera::DEFAULT_Z_FAR;

	protected:
		virtual void _onUpdateProjMatrix(const float deltaTime, glm::mat4 &projMatrix) noexcept override;

	public:
		constexpr void setFov(const float fov) noexcept;
		constexpr void resetFov() noexcept;
		constexpr void adjustFov(const float delta) noexcept;

		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(const int width, const int height) noexcept;

		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

		// bounds
		constexpr void setMaxFov(const float maxFov) noexcept;
		constexpr void setMinFov(const float minFov) noexcept;

		virtual ~PerspectiveCamera() = default;
	};

	constexpr void PerspectiveCamera::setFov(const float fov) noexcept
	{
		__fov = glm::clamp(fov, __minFov, __maxFov);
	}

	constexpr void PerspectiveCamera::resetFov() noexcept
	{
		setFov(Constant::Camera::DEFAULT_FOV);
	}

	constexpr void PerspectiveCamera::adjustFov(const float delta) noexcept
	{
		setFov(__fov + delta);
	}

	constexpr void PerspectiveCamera::setAspectRatio(const float ratio) noexcept
	{
		__aspectRatio = ratio;
	}

	constexpr void PerspectiveCamera::setAspectRatio(const int width, const int height) noexcept
	{
		setAspectRatio(float(width) / float(height));
	}

	constexpr void PerspectiveCamera::setNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	constexpr void PerspectiveCamera::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}

	constexpr void PerspectiveCamera::setMaxFov(const float maxFov) noexcept
	{
		__maxFov = maxFov;
	}

	constexpr void PerspectiveCamera::setMinFov(const float minFov) noexcept
	{
		__minFov = minFov;
	}
}
