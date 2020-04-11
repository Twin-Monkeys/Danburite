#include "SilhouetteMaterialComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void SilhouetteMaterialComponent::_deploySilhouetteComponent(UniformSetter &materialSetter) const noexcept
	{
		materialSetter.setUniformFloat(ShaderIdentifier::Name::Material::Z_NEAR, __zNear);
		materialSetter.setUniformFloat(ShaderIdentifier::Name::Material::Z_FAR, __zFar);
	}
}