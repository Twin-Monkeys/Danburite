#include "OutliningMaterialComponent.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	void OutliningMaterialComponent::_deployOutliningComponent(UniformSetter &materialSetter) const noexcept
	{
		materialSetter.setUniformVec4(ShaderIdentifier::Name::Material::OUTLINE_COLOR, __outlineColor);
		materialSetter.setUniformFloat(ShaderIdentifier::Name::Material::THICKNESS_RATIO, __outlineThicknessRatio);
	}
}