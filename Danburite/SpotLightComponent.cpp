#include "SpotLightComponent.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void SpotLightComponent::_deploySpotComponent(const size_t lightIndex, LightUniformInterface &lightUI) noexcept
	{
		lightUI.innerCutOff = { lightIndex, __innerCutOff };
		lightUI.innerCutOff = { lightIndex, __outerCutOff };
	}

	void SpotLightComponent::setCutOff(const float innerAngle, const float outerAngle) noexcept
	{
		__innerCutOff = cosf(innerAngle);
		__outerCutOff = cosf(outerAngle);
	}
}
