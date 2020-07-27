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

	void LightBaseComponent::setAlbedo(const glm::vec3 &albedo) noexcept
	{
		__albedo = albedo;
	}

	void LightBaseComponent::setAlbedo(const float r, const float g, const float b) noexcept
	{
		setAlbedo({ r, g, b });
	}

	void LightBaseComponent::setAmbientStrength(const float strength) noexcept
	{
		__ambientStrength = strength;
	}

	void LightBaseComponent::setDiffuseStrength(const float strength) noexcept
	{
		__diffuseStrength = strength;
	}

	void LightBaseComponent::setSpecularStrength(const float strength) noexcept
	{
		__specularStrength = strength;
	}
}