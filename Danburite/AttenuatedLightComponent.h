#pragma once

#include "LightUniformSetter.h"
#include "Constant.h"

namespace Danburite
{
	class AttenuatedLightComponent abstract
	{
	private:
		float __attConst	= Constant::Light::AttenuatedComponent::ATT_CONST;
		float __attLinear	= Constant::Light::AttenuatedComponent::ATT_LINEAR;
		float __attQuad		= Constant::Light::AttenuatedComponent::ATT_QUAD;

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