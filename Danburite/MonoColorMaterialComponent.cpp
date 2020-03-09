#include "MonoColorMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "UniformSetter.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void MonoColorMaterialComponent::_onDeploy(UniformSetter &materialSetter) const noexcept
	{
		materialSetter.setUniformVec4(ShaderIdentifier::Name::Material::DIFFUSE_COLOR, __color);
	}
}