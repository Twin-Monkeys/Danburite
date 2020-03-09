#include "OutliningMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "UniformSetter.h"

using namespace ObjectGL;

namespace Danburite
{
	void OutliningMaterialComponent::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		uniformSetter.setUniformVec4(ShaderIdentifier::Name::Material::OUTLINE_COLOR, __outlineColor);
		uniformSetter.setUniformFloat(ShaderIdentifier::Name::Material::THICKNESS_RATIO, __outlineThicknessRatio);
	}
}