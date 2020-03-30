#include "RefractionMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"
#include "UniformSetter.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void RefractionMaterialComponent::_onDeploy(UniformSetter &materialSetter) const noexcept
	{
		using namespace ShaderIdentifier;

		materialSetter.setUniformUvec2(Name::Material::ENVIRONMENT_TEX, TextureUtil::getHandleIfExist(__pEnvTex));
		materialSetter.setUniformUvec2(Name::Material::NORMAL_TEX, TextureUtil::getHandleIfExist(__pNormalTex));
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