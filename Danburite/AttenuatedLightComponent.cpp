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
}
