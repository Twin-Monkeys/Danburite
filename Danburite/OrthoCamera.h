#pragma once

#include "TransformableCamera.h"
#include "Constant.h"

namespace Danburite
{
	class OrthoCamera : public TransformableCamera
	{
	private:
		float __maxOrthoHeight = Constant::Camera::MAX_ORTHO_HEIGHT;
		float __minOrthoHeight = Constant::Camera::MIN_ORTHO_HEIGHT;
		float __orthoHeight = Constant::Camera::DEFAULT_ORTHO_HEIGHT;

		float __aspectRatio = Constant::Camera::DEFAULT_ASPECT_RATIO;

		float __zNear		= Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar		= Constant::Camera::DEFAULT_Z_FAR;

	protected:
		virtual void _onUpdateProjMatrix(const float deltaTime, glm::mat4 &projMatrix) noexcept override;

	public:
		constexpr void setOrthoHeight(const float height) noexcept;
		constexpr void resetOrthoHeight() noexcept;
		constexpr void adjustOrthoHeight(const float delta) noexcept;

		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(const int width, const int height) noexcept;

		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

		// bounds
		constexpr void setMaxOrthoHeight(const float maxHeight) noexcept;
		constexpr void setMinOrthoHeight(const float minHeight) noexcept;

		virtual ~OrthoCamera() = default;
	};

	constexpr void OrthoCamera::setOrthoHeight(const float height) noexcept
	{
		__orthoHeight = glm::clamp(height, __minOrthoHeight, __maxOrthoHeight);
	}

	constexpr void OrthoCamera::resetOrthoHeight() noexcept
	{
		setOrthoHeight(Constant::Camera::DEFAULT_ORTHO_HEIGHT);
	}

	constexpr void OrthoCamera::adjustOrthoHeight(const float delta) noexcept
	{
		setOrthoHeight(__orthoHeight + delta);
	}

	constexpr void OrthoCamera::setAspectRatio(const float ratio) noexcept
	{
		__aspectRatio = ratio;
	}

	constexpr void OrthoCamera::setAspectRatio(const int width, const int height) noexcept
	{
		setAspectRatio(float(width) / float(height));
	}

	constexpr void OrthoCamera::setNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	constexpr void OrthoCamera::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}

	constexpr void OrthoCamera::setMaxOrthoHeight(const float maxHeight) noexcept
	{
		__maxOrthoHeight = maxHeight;
	}

	constexpr void OrthoCamera::setMinOrthoHeight(const float minHeight) noexcept
	{
		__minOrthoHeight = minHeight;
	}
}
