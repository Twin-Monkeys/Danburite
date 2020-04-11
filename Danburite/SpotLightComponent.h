#pragma once

#include <glm/gtc/constants.hpp>
#include "LightUniformSetter.h"

namespace Danburite
{
	class SpotLightComponent abstract
	{
	private:
		float __innerCutOff = cosf(glm::quarter_pi<float>() * .5f);
		float __outerCutOff = cosf(glm::quarter_pi<float>() * .6f);

	protected:
		void _deploySpotComponent(LightUniformSetter &lightSetter) noexcept;

	public:
		void setCutOff(const float innerAngle, const float outerAngle) noexcept;

		virtual ~SpotLightComponent() = default;
	};
}