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

		constexpr void setDepthBakingOrthoHeight(const float height) noexcept;
		constexpr void resetDepthBakingOrthoHeight() noexcept;
		constexpr void adjustDepthBakingOrthoHeight(const float delta) noexcept;

		constexpr void setDepthBakingAspectRatio(const float ratio) noexcept;
		constexpr void setDepthBakingAspectRatio(const int width, const int height) noexcept;

		constexpr void setDepthBakingNear(const float zNear) noexcept;
		constexpr void setDepthBakingFar(const float zFar) noexcept;

		// bounds
		constexpr void setDepthBakingMaxOrthoHeight(const float maxHeight) noexcept;
		constexpr void setDepthBakingMinOrthoHeight(const float minHeight) noexcept;
	};

	constexpr void OrthoCameraLight::setDepthBakingOrthoHeight(const float height) noexcept
	{
		__camera.setOrthoHeight(height);
	}

	constexpr void OrthoCameraLight::resetDepthBakingOrthoHeight() noexcept
	{
		__camera.resetOrthoHeight();
	}

	constexpr void OrthoCameraLight::adjustDepthBakingOrthoHeight(const float delta) noexcept
	{
		__camera.adjustOrthoHeight(delta);
	}

	constexpr void OrthoCameraLight::setDepthBakingAspectRatio(const float ratio) noexcept
	{
		__camera.setAspectRatio(ratio);
	}

	constexpr void OrthoCameraLight::setDepthBakingAspectRatio(const int width, const int height) noexcept
	{
		__camera.setAspectRatio(width, height);
	}

	constexpr void OrthoCameraLight::setDepthBakingNear(const float zNear) noexcept
	{
		__camera.setNear(zNear);
	}

	constexpr void OrthoCameraLight::setDepthBakingFar(const float zFar) noexcept
	{
		__camera.setFar(zFar);
	}

	constexpr void OrthoCameraLight::setDepthBakingMaxOrthoHeight(const float maxHeight) noexcept
	{
		__camera.setMaxOrthoHeight(maxHeight);
	}

	constexpr void OrthoCameraLight::setDepthBakingMinOrthoHeight(const float minHeight) noexcept
	{
		__camera.setMinOrthoHeight(minHeight);
	}
}