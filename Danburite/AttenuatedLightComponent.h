#pragma once

#include "LightUniformSetter.h"
#include "Constant.h"

namespace Danburite
{
	class AttenuatedLightComponent abstract
	{
	private:
		float __attConst		= Constant::Light::AttenuatedComponent::ATT_CONST;
		float __attLinear		= Constant::Light::AttenuatedComponent::ATT_LINEAR;
		float __attQuad			= Constant::Light::AttenuatedComponent::ATT_QUAD;
		float __validDistance	= std::numeric_limits<float>::max();

	protected:
		void _setValidDistance(
			const float luminanceTolerance,	const glm::vec3 &albedo,
			const float ambientStrength, const float diffuseStrength, const float specularStrength) noexcept;

		void _deployAttenuatedComponent(LightUniformSetter &lightSetter) noexcept;

	public:
		constexpr void setAttenuation(const float constant, const float linear, const float quadratic) noexcept;
		void setLuminanceTolerance(const float tolerance) noexcept;

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