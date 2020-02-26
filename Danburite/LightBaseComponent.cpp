#include "LightBaseComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void LightBaseComponent::_onDeploy(LightUniformSetter &target) noexcept
	{
		target.setUniformVec3(ShaderIdentifier::Name::Light::ALBEDO, __albedo);
		target.setUniformFloat(ShaderIdentifier::Name::Light::AMBIENT_STRENGTH, __ambientStrength);
		target.setUniformFloat(ShaderIdentifier::Name::Light::DIFFUSE_STRENGTH, __diffuseStrength);
		target.setUniformFloat(ShaderIdentifier::Name::Light::SPECULAR_STRENGTH, __specularStrength);
	}
}