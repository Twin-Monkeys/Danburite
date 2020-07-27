#include "AttenuatedLightComponent.h"
#include "ShaderIdentifier.h"

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
		const float maxLuminance = (fmaxf(fmaxf(maxLight.r, maxLight.g), maxLight.b) / luminanceTolerance);

		const float discriminant =
			((__attLinear * __attLinear) - (4.f * __attQuad * (__attConst - maxLuminance)));

		__validDistance = (((-__attLinear) + ((discriminant <= 0.f) ? 0.f : sqrtf(discriminant))) / (2.f * __attQuad));
	}

	void AttenuatedLightComponent::_deployAttenuatedComponent(LightUniformSetter &lightSetter) noexcept
	{
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_CONST, __attConst);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_LINEAR, __attLinear);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_QUAD, __attQuad);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::VALID_DISTANCE, __validDistance);
	}
}
