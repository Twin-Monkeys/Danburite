#include "MonoColorMaterialComponent.h"
#include "ShaderIdentifier.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void MonoColorMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		Program &monoColorProgram = materialSetter.getProgram(ProgramType::MONO_COLOR);

		monoColorProgram.setUniformVec4(ShaderIdentifier::Name::Material::DIFFUSE_COLOR, __color);
	}
}