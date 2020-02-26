#include "OutliningMaterialComponent.h"
#include "ShaderIdentifier.h"

using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void OutliningMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		Program& monoColorProgram = materialSetter.getProgram(ProgramType::OUTLINE);

		monoColorProgram.setUniformVec4(ShaderIdentifier::Name::Material::OUTLINE_COLOR, __outlineColor);
		monoColorProgram.setUniformFloat(ShaderIdentifier::Name::Material::THICKNESS_RATIO, __outlineThicknessRatio);
	}
}