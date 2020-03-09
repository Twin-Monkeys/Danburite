#include "SilhouetteMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "UniformSetter.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void SilhouetteMaterialComponent::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		uniformSetter.setUniformFloat(ShaderIdentifier::Name::Material::Z_NEAR, __zNear);
		uniformSetter.setUniformFloat(ShaderIdentifier::Name::Material::Z_FAR, __zFar);
	}
}