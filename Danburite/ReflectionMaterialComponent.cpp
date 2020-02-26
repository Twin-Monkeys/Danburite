#include "ReflectionMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void ReflectionMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		TextureUtil::bindIfExist(__pEnvTex, ShaderIdentifier::Value::Material::ENVIRONMENT_TEX_LOCATION);
		TextureUtil::bindIfExist(__pNormalTex, ShaderIdentifier::Value::Material::NORMAL_TEX_LOCATION);
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