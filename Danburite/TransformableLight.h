#pragma once

#include "Light.h"
#include "AnimatableTransform.h"
#include "Updatable.h"

namespace Danburite
{
	class TransformableLight abstract : public Light, public Updatable
	{
	protected:
		void _deployDirection(LightUniformSetter &lightSetter) const noexcept;
		void _deployPosition(LightUniformSetter &lightSetter) const noexcept;

	public:
		TransformableLight(const LightType type, const DepthBakingType depthBakingType);

		virtual AnimatableTransform &getTransform() noexcept = 0;
		virtual const AnimatableTransform &getTransform() const noexcept = 0;
	};
}