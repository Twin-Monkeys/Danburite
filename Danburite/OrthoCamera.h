#pragma once

#include "TransformableCamera.h"
#include "Constant.h"

namespace Danburite
{
	class OrthoCamera : public TransformableCamera
	{
	private:
		float __xOrthoLeft		= Constant::Camera::DEFAULT_X_ORTHO_LEFT;
		float __xOrthoRight		= Constant::Camera::DEFAULT_X_ORTHO_RIGHT;
		float __yOrthoBottom	= Constant::Camera::DEFAULT_Y_ORTHO_BOTTOM;
		float __yOrthoTop		= Constant::Camera::DEFAULT_Y_ORTHO_TOP;
		float __zOrthoNear		= Constant::Camera::DEFAULT_Z_ORTHO_NEAR;
		float __zOrthoFar		= Constant::Camera::DEFAULT_Z_ORTHO_FAR;

	protected:
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept override;

	public:
		constexpr void setOrthoLeft(const float xLeft) noexcept;
		constexpr void setOrthoRight(const float xRight) noexcept;
		constexpr void setOrthoBottom(const float yBottom) noexcept;
		constexpr void setOrthoTop(const float yTop) noexcept;
		constexpr void setOrthoNear(const float zNear) noexcept;
		constexpr void setOrthoFar(const float zFar) noexcept;

		constexpr void setOrtho(
			const float xLeft, const float xRight,
			const float yBottom, const float yTop,
			const float zNear, const float zFar) noexcept;

		virtual ~OrthoCamera() = default;
	};

	constexpr void OrthoCamera::setOrthoLeft(const float xLeft) noexcept
	{
		__xOrthoLeft = xLeft;
	}

	constexpr void OrthoCamera::setOrthoRight(const float xRight) noexcept
	{
		__xOrthoRight = xRight;
	}

	constexpr void OrthoCamera::setOrthoBottom(const float yBottom) noexcept
	{
		__yOrthoBottom = yBottom;
	}

	constexpr void OrthoCamera::setOrthoTop(const float yTop) noexcept
	{
		__yOrthoTop = yTop;
	}

	constexpr void OrthoCamera::setOrthoNear(const float zNear) noexcept
	{
		__zOrthoNear = zNear;
	}

	constexpr void OrthoCamera::setOrthoFar(const float zFar) noexcept
	{
		__zOrthoFar = zFar;
	}

	constexpr void OrthoCamera::setOrtho(
		const float xLeft, const float xRight,
		const float yBottom, const float yTop,
		const float zNear, const float zFar) noexcept
	{
		__xOrthoLeft = xLeft;
		__xOrthoRight = xRight;
		__yOrthoBottom = yBottom;
		__yOrthoTop = yTop;
		__zOrthoNear = zNear;
		__zOrthoFar = zFar;
	}
}
