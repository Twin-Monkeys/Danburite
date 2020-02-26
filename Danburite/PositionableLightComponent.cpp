#include "PositionableLightComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void PositionableLightComponent::_onDeploy(LightUniformSetter &target) noexcept
	{
		target.setUniformVec3(ShaderIdentifier::Name::Light::POSITION, __pos);
	}
}
