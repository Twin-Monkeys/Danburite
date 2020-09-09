#pragma once

#include "TransformableLight.h"
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
		virtual void _onDeployShadowData(LightUniformInterface &lightUI) noexcept override;
		virtual void _onBakeDepthMap(BatchProcessor<SceneObject> &drawer) noexcept override;
		virtual void _onChangeShadowEnabled(const bool enabled) noexcept override;

	public:
		PerspectiveLight(const LightType type, const GLuint index);

		constexpr void setDepthBakingNear(const float zNear) noexcept;
		constexpr void setDepthBakingFar(const float zFar) noexcept;

		virtual const glm::ivec2 &getDepthMapSize() noexcept override;
		virtual void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual Transform &getTransform() noexcept override;
		virtual const Transform &getTransform() const noexcept override;
		virtual void update(const float delta) noexcept override;
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