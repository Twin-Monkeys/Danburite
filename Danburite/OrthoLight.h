#pragma once

#include "TransformableLight.h"
#include "OrthoCamera.h"
#include "DepthBaker2D.h"

namespace Danburite
{
	class OrthoLight abstract : public TransformableLight
	{
	private:
		OrthoCamera __camera;
		DepthBaker2D __depthBaker;

	protected:
		virtual void _onDeployShadowData(LightUniformSetter &lightSetter) noexcept override;
		virtual void _onBakeDepthMap(Drawer &drawer) noexcept override;

	public:
		OrthoLight(const LightType type);

		constexpr void setDepthBakingOrthoHeight(const float height) noexcept;
		constexpr void resetDepthBakingOrthoHeight() noexcept;
		constexpr void adjustDepthBakingOrthoHeight(const float delta) noexcept;

		constexpr void setDepthBakingAspectRatio(const float ratio) noexcept;
		constexpr void setDepthBakingAspectRatio(const int width, const int height) noexcept;

		constexpr void setDepthBakingNear(const float zNear) noexcept;
		constexpr void setDepthBakingFar(const float zFar) noexcept;

		constexpr void setDepthBakingMaxOrthoHeight(const float maxHeight) noexcept;
		constexpr void setDepthBakingMinOrthoHeight(const float minHeight) noexcept;

		virtual void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual AnimatableTransform &getTransform() noexcept override;
		virtual const AnimatableTransform &getTransform() const noexcept override;
		virtual void update(const float deltaTime) noexcept override;
	};

	constexpr void OrthoLight::setDepthBakingOrthoHeight(const float height) noexcept
	{
		__camera.setOrthoHeight(height);
	}

	constexpr void OrthoLight::resetDepthBakingOrthoHeight() noexcept
	{
		__camera.resetOrthoHeight();
	}

	constexpr void OrthoLight::adjustDepthBakingOrthoHeight(const float delta) noexcept
	{
		__camera.adjustOrthoHeight(delta);
	}

	constexpr void OrthoLight::setDepthBakingAspectRatio(const float ratio) noexcept
	{
		__camera.setAspectRatio(ratio);
	}

	constexpr void OrthoLight::setDepthBakingAspectRatio(const int width, const int height) noexcept
	{
		__camera.setAspectRatio(width, height);
	}

	constexpr void OrthoLight::setDepthBakingNear(const float zNear) noexcept
	{
		__camera.setNear(zNear);
	}

	constexpr void OrthoLight::setDepthBakingFar(const float zFar) noexcept
	{
		__camera.setFar(zFar);
	}

	constexpr void OrthoLight::setDepthBakingMaxOrthoHeight(const float maxHeight) noexcept
	{
		__camera.setMaxOrthoHeight(maxHeight);
	}

	constexpr void OrthoLight::setDepthBakingMinOrthoHeight(const float minHeight) noexcept
	{
		__camera.setMinOrthoHeight(minHeight);
	}
}