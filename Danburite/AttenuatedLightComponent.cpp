#include "AttenuatedLightComponent.h"
#include "ShaderIdentifier.h"
#include <glm/gtc/epsilon.hpp>

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void AttenuatedLightComponent::_setValidDistance(
		const float luminanceTolerance, const vec3 &albedo,
		const float ambientStrength, const float diffuseStrength, const float specularStrength) noexcept
	{
		const vec3 &maxLight = (albedo * (ambientStrength + diffuseStrength + specularStrength));
		const float maxLuminance = fmaxf(fmaxf(maxLight.r, maxLight.g), maxLight.b);

		if (epsilonEqual(luminanceTolerance, 0.f, epsilon<float>()))
		{
			__validDistance = Constant::Light::AttenuatedComponent::MAX_VALID_DISTANCE;
		}
		else if (epsilonEqual(__attQuad, 0.f, epsilon<float>()))
		{
			if (epsilonEqual(__attLinear, 0.f, epsilon<float>()))
				__validDistance = Constant::Light::AttenuatedComponent::MAX_VALID_DISTANCE;
			else
				__validDistance = (((maxLuminance / luminanceTolerance) - __attConst) / __attLinear);
		}
		else
		{
			const float discriminant =
				((__attLinear * __attLinear) - (4.f * __attQuad * (__attConst - (maxLuminance / luminanceTolerance))));

			__validDistance = (((-__attLinear) + ((discriminant <= 0.f) ? 0.f : sqrtf(discriminant))) / (2.f * __attQuad));
		}
	}

	void AttenuatedLightComponent::_deployAttenuatedComponent(LightUniformSetter &lightSetter) noexcept
	{
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_CONST, __attConst);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_LINEAR, __attLinear);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_QUAD, __attQuad);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::VALID_DISTANCE, __validDistance);
	}

	void AttenuatedLightComponent::setAttenuation(
		const float constant, const float linear, const float quadratic) noexcept
	{
		__attConst = constant;
		__attLinear = linear;
		__attQuad = quadratic;
	}
}
