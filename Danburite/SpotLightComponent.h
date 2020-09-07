#pragma once

#include <glm/gtc/constants.hpp>
#include "Constant.h"
#include "DeferredUniformBuffer.h"
#include "LightUniformInterface.h"

namespace Danburite
{
	class SpotLightComponent abstract
	{
	private:
		float __innerCutOff = cosf(Constant::Light::SpotComponent::INNER_CUTOFF_ANGLE);
		float __outerCutOff = cosf(Constant::Light::SpotComponent::OUTER_CUTOFF_ANGLE);

	protected:
		void _deploySpotComponent(const size_t lightIndex, DeferredUniformBuffer<LightUniformInterface> &lightUB) noexcept;

	public:
		void setCutOff(const float innerAngle, const float outerAngle) noexcept;

		virtual ~SpotLightComponent() = default;
	};
}