#include "SpotLightComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void SpotLightComponent::_onDeploy(LightUniformSetter &target) noexcept
	{
		target.setUniformFloat(ShaderIdentifier::Name::Light::INNER_CUTOFF, __innerCutOff);
		target.setUniformFloat(ShaderIdentifier::Name::Light::OUTER_CUTOFF, __outerCutOff);
	}

	void SpotLightComponent::setCutOff(const float innerAngle, const float outerAngle) noexcept
	{
		__innerCutOff = cosf(innerAngle);
		__outerCutOff = cosf(outerAngle);
	}
}
