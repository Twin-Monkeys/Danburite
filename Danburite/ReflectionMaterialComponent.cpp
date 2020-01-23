#include "ReflectionMaterialComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void ReflectionMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		if (__pEnvTex)
			__pEnvTex->bind(ShaderIdentifier::Value::Material::ENVIRONMENT_TEX_LOCATION);

		if (__pNormalTex)
			__pNormalTex->bind(ShaderIdentifier::Value::Material::NORMAL_TEX_LOCATION);
	}

	void ReflectionMaterialComponent::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}

	void ReflectionMaterialComponent::setNormalTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pNormalTex = pTexture;
	}
}