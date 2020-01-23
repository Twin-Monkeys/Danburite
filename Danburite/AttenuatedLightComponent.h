#pragma once

#include "LightUniformDeployable.h"

namespace Danburite
{
	class AttenuatedLightComponent abstract : virtual public LightUniformDeployable
	{
	private:
		float __attConst = 1.f;
		float __attLinear = 0.f;
		float __attQuad = 0.f;

	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept override;

	public:
		void setAttenuation(const float constant, const float linear, const float quadratic) noexcept;

		virtual ~AttenuatedLightComponent() = default;
	};
}