#pragma once

#include "TransformableCameraLight.h"
#include "OrthoCamera.h"

namespace Danburite
{
	class OrthoCameraLight abstract : public TransformableCameraLight
	{
	private:
		OrthoCamera __camera;

	protected:
		virtual TransformableCamera &_getCamera() noexcept override;
		virtual const TransformableCamera &_getCamera() const noexcept override;

	public:
		OrthoCameraLight(const LightType type);

		constexpr void setDepthBakingOrthoLeft(const float xLeft) noexcept;
		constexpr void setDepthBakingOrthoRight(const float xRight) noexcept;
		constexpr void setDepthBakingOrthoBottom(const float yBottom) noexcept;
		constexpr void setDepthBakingOrthoTop(const float yTop) noexcept;
		constexpr void setDepthBakingOrthoNear(const float zNear) noexcept;
		constexpr void setDepthBakingOrthoFar(const float zFar) noexcept;

		constexpr void setDepthBakingOrtho(
			const float xLeft, const float xRight,
			const float yBottom, const float yTop,
			const float zNear, const float zFar) noexcept;
	};

	constexpr void OrthoCameraLight::setDepthBakingOrthoLeft(const float xLeft) noexcept
	{
		__camera.setOrthoLeft(xLeft);
	}

	constexpr void OrthoCameraLight::setDepthBakingOrthoRight(const float xRight) noexcept
	{
		__camera.setOrthoRight(xRight);
	}

	constexpr void OrthoCameraLight::setDepthBakingOrthoBottom(const float yBottom) noexcept
	{
		__camera.setOrthoBottom(yBottom);
	}

	constexpr void OrthoCameraLight::setDepthBakingOrthoTop(const float yTop) noexcept
	{
		__camera.setOrthoTop(yTop);
	}

	constexpr void OrthoCameraLight::setDepthBakingOrthoNear(const float zNear) noexcept
	{
		__camera.setOrthoNear(zNear);
	}

	constexpr void OrthoCameraLight::setDepthBakingOrthoFar(const float zFar) noexcept
	{
		__camera.setOrthoFar(zFar);
	}

	constexpr void OrthoCameraLight::setDepthBakingOrtho(
		const float xLeft, const float xRight,
		const float yBottom, const float yTop,
		const float zNear, const float zFar) noexcept
	{
		__camera.setOrtho(xLeft, xRight, yBottom, yTop, zNear, zFar);
	}
}