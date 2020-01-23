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

	const vec3 &LightBaseComponent::getAlbedo() const noexcept
	{
		return __albedo;
	}

	void LightBaseComponent::setAlbedo(const vec3 &albedo) noexcept
	{
		__albedo = albedo;
	}

	void LightBaseComponent::setAlbedo(const float r, const float g, const float b) noexcept
	{
		setAlbedo({ r, g, b });
	}

	float LightBaseComponent::getAmbientStrength() const noexcept
	{
		return __ambientStrength;
	}

	void LightBaseComponent::setAmbientStrength(const float strength) noexcept
	{
		__ambientStrength = strength;
	}

	float LightBaseComponent::getDiffuseStrength() const noexcept
	{
		return __diffuseStrength;
	}

	void LightBaseComponent::setDiffuseStrength(const float strength) noexcept
	{
		__diffuseStrength = strength;
	}

	float LightBaseComponent::getSpecularStrength() const noexcept
	{
		return __specularStrength;
	}

	void LightBaseComponent::setSpecularStrength(const float strength) noexcept
	{
		__specularStrength = strength;
	}
}