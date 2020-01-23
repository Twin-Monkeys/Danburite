#include "AttenuatedLightComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void AttenuatedLightComponent::_onDeploy(LightUniformSetter &target) noexcept
	{
		target.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_CONST, __attConst);
		target.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_LINEAR, __attLinear);
		target.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_QUAD, __attQuad);
	}

	void AttenuatedLightComponent::setAttenuation(
		const float constant, const float linear, const float quadratic) noexcept
	{
		__attConst = constant;
		__attLinear = linear;
		__attQuad = quadratic;
	}
}
