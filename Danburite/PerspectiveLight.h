#pragma once

#include "TransformableLight.h"
#include "Transform.h"

namespace Danburite
{
	class PerspectiveLight abstract : public TransformableLight
	{
	private:
		Transform __transform;

	protected:
		virtual void _onDeployShadowData(LightUniformSetter& lightSetter) noexcept override;
		virtual void _onBakeDepthMap(Drawer& drawer) noexcept override;

	public:
		PerspectiveLight(const LightType type);

		virtual void setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept override;

		virtual Transform &getTransform() noexcept override;
		virtual const Transform &getTransform() const noexcept override;
		virtual void update() noexcept override;
	};
}