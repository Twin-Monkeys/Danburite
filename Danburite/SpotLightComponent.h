#pragma once

#include "LightUniformDeployable.h"
#include <glm/gtc/constants.hpp>

namespace Danburite
{
	class SpotLightComponent abstract : virtual public LightUniformDeployable
	{
	private:
		float __innerCutOff = cosf(glm::quarter_pi<float>() * .5f);
		float __outerCutOff = cosf(glm::quarter_pi<float>() * .6f);

	protected:
		virtual void _onDeploy(LightUniformSetter &lightSetter) noexcept override;

	public:
		void setCutOff(const float innerAngle, const float outerAngle) noexcept;

		virtual ~SpotLightComponent() = default;
	};
}