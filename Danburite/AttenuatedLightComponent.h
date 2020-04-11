#pragma once

#include "LightUniformSetter.h"

namespace Danburite
{
	class AttenuatedLightComponent abstract
	{
	private:
		float __attConst = 1.f;
		float __attLinear = 0.f;
		float __attQuad = 0.f;

	protected:
		void _deployAttenuatedComponent(LightUniformSetter &lightSetter) noexcept;

	public:
		constexpr void setAttenuation(const float constant, const float linear, const float quadratic) noexcept;

		virtual ~AttenuatedLightComponent() = default;
	};

	constexpr void AttenuatedLightComponent::setAttenuation(
		const float constant, const float linear, const float quadratic) noexcept
	{
		__attConst = constant;
		__attLinear = linear;
		__attQuad = quadratic;
	}
}