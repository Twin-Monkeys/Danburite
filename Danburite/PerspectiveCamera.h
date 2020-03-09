#pragma once

#include "Camera.h"
#include "Constant.h"
#include "CameraTransform.h"

namespace Danburite
{
	class PerspectiveCamera : public Camera
	{
	private:
		CameraTransform __transform;

		// projection factors

		float __maxPitch = Constant::Camera::MAX_PITCH;
		float __maxFov = Constant::Camera::MAX_FOV;
		float __minFov = Constant::Camera::MIN_FOV;

		float __fov = Constant::Camera::DEFAULT_FOV;
		float __aspectRatio = 1.f;

		float __zNear = Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar = Constant::Camera::DEFAULT_Z_FAR;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept override;
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept override;
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) noexcept override;

	public:
		PerspectiveCamera() noexcept;

		constexpr CameraTransform &getTransform() noexcept;
		constexpr const CameraTransform &getTransform() const noexcept;

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

		virtual ~PerspectiveCamera() = default;
	};

	constexpr CameraTransform& PerspectiveCamera::getTransform() noexcept
	{
		return __transform;
	}

	constexpr const CameraTransform& PerspectiveCamera::getTransform() const noexcept
	{
		return __transform;
	}

	constexpr void PerspectiveCamera::setFov(const float fov) noexcept
	{
		float validFov = fov;

		if (validFov > __maxFov)
			validFov = __maxFov;
		else if (validFov < __minFov)
			validFov = __minFov;

		__fov = validFov;
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

	constexpr void PerspectiveCamera::setMaxPitch(const float maxPitch) noexcept
	{
		__maxPitch = maxPitch;
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
