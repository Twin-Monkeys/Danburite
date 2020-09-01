#pragma once

#include "Light.h"
#include "Transform.h"
#include "Updatable.h"

namespace Danburite
{
	class TransformableLight abstract : public Light, public Updatable
	{
	protected:
		void _deployDirection(DeferredUniformBuffer<LightUniformInterface> &lightUB) const noexcept;
		void _deployPosition(DeferredUniformBuffer<LightUniformInterface> &lightUB) const noexcept;

	public:
		TransformableLight(
			const LightType type, const LightVolumeType volumeType,
			const DepthBakingType depthBakingType, const GLuint index);

		virtual Transform &getTransform() noexcept = 0;
		virtual const Transform &getTransform() const noexcept = 0;
	};
}