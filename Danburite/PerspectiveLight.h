#pragma once

#include "TransformableLight.h"
#include "Transform.h"
#include "DepthBakerCubemap.h"

namespace Danburite
{
	class PerspectiveLight abstract : public TransformableLight
	{
	private:
		Transform __transform;
		DepthBakerCubemap __depthBaker;

		float __zNear	= Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar	= Constant::Camera::DEFAULT_Z_FAR;

	protected:
		virtual void _onDeployShadowData(LightUniformSetter& lightSetter) noexcept override;
		virtual void _onBakeDepthMap(Drawer& drawer) noexcept override;

	public:
		PerspectiveLight(const LightType type);

		constexpr void setDepthBakingNear(const float zNear) noexcept;
		constexpr void setDepthBakingFar(const float zFar) noexcept;

		virtual void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual Transform &getTransform() noexcept override;
		virtual const Transform &getTransform() const noexcept override;
		virtual void update() noexcept override;
	};

	constexpr void PerspectiveLight::setDepthBakingNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	constexpr void PerspectiveLight::setDepthBakingFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}
}