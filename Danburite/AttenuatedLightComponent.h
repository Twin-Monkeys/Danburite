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

		constexpr float _getValidDistance() const noexcept;

		void _deployAttenuatedComponent(LightUniformSetter &lightSetter) noexcept;

	public:
		virtual void setAttenuation(const float constant, const float linear, const float quadratic) noexcept;

		virtual ~AttenuatedLightComponent() = default;
	};

	constexpr float AttenuatedLightComponent::_getValidDistance() const noexcept
	{
		return __validDistance;
	}
}