#include "RefractionMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void RefractionMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		TextureUtil::bindIfExist(__pEnvTex, ShaderIdentifier::Value::Material::ENVIRONMENT_TEX_LOCATION);
		TextureUtil::bindIfExist(__pNormalTex, ShaderIdentifier::Value::Material::NORMAL_TEX_LOCATION);
	}

	void RefractionMaterialComponent::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}

	void RefractionMaterialComponent::setNormalTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pNormalTex = pTexture;
	}
}