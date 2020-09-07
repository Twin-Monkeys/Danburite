#include "SpotLightComponent.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void SpotLightComponent::_deploySpotComponent(const size_t lightIndex, DeferredUniformBuffer<LightUniformInterface> &lightUB) noexcept
	{
		LightUniformInterface &lightUI = lightUB.getInterface();

		lightUI.innerCutOff = { lightIndex, __innerCutOff };
		lightUI.innerCutOff = { lightIndex, __outerCutOff };
	}

	void SpotLightComponent::setCutOff(const float innerAngle, const float outerAngle) noexcept
	{
		__innerCutOff = cosf(innerAngle);
		__outerCutOff = cosf(outerAngle);
	}
}
