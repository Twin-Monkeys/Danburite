#include "LightBaseComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void LightBaseComponent::_deployBaseComponent(LightUniformSetter &lightSetter) noexcept
	{
		lightSetter.setUniformVec3(ShaderIdentifier::Name::Light::ALBEDO, __albedo);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::AMBIENT_STRENGTH, __ambientStrength);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::DIFFUSE_STRENGTH, __diffuseStrength);
		lightSetter.setUniformFloat(ShaderIdentifier::Name::Light::SPECULAR_STRENGTH, __specularStrength);
	}
}