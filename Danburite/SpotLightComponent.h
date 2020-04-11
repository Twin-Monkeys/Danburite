#pragma once

#include <glm/gtc/constants.hpp>
#include "LightUniformSetter.h"
#include "Constant.h"

namespace Danburite
{
	class SpotLightComponent abstract
	{
	private:
		float __innerCutOff = cosf(Constant::Light::SpotComponent::INNER_CUTOFF_ANGLE);
		float __outerCutOff = cosf(Constant::Light::SpotComponent::OUTER_CUTOFF_ANGLE);

	protected:
		void _deploySpotComponent(LightUniformSetter &lightSetter) noexcept;

	public:
		void setCutOff(const float innerAngle, const float outerAngle) noexcept;

		virtual ~SpotLightComponent() = default;
	};
}