#pragma once

#include "TransformableCamera.h"
#include "Constant.h"

namespace Danburite
{
	class OrthoCamera : public TransformableCamera
	{
	private:
		float __xLeft		= Constant::Camera::DEFAULT_X_LEFT;
		float __xRight		= Constant::Camera::DEFAULT_X_RIGHT;
		float __yBottom		= Constant::Camera::DEFAULT_Y_BOTTOM;
		float __yTop		= Constant::Camera::DEFAULT_Y_TOP;
		float __zNear		= Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar		= Constant::Camera::DEFAULT_Z_FAR;

	protected:
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept override;

	public:
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

		virtual ~OrthoCamera() = default;
	};

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
}
