#include "AttenuatedLightComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void AttenuatedLightComponent::_deployAttenuatedComponent(LightUniformSetter &lightSetter) noexcept
	{
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_CONST, __attConst);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_LINEAR, __attLinear);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::ATTENUATION_QUAD, __attQuad);
	}
}
