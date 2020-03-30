#include "PhongMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"
#include "UniformSetter.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void PhongMaterialComponent::_onDeploy(UniformSetter &materialSetter) const noexcept
	{
		using namespace ShaderIdentifier;

		materialSetter.setUniformFloat(Name::Material::SHININESS, __shininess);
		materialSetter.setUniformUvec2(Name::Material::AMBIENT_TEX, TextureUtil::getHandleIfExist(__pAmbientTex));
		materialSetter.setUniformUvec2(Name::Material::DIFFUSE_TEX, TextureUtil::getHandleIfExist(__pDiffuseTex));
		materialSetter.setUniformUvec2(Name::Material::SPECULAR_TEX, TextureUtil::getHandleIfExist(__pSpecularTex));
		materialSetter.setUniformUvec2(Name::Material::EMISSIVE_TEX, TextureUtil::getHandleIfExist(__pEmissiveTex));
		materialSetter.setUniformUvec2(Name::Material::SHININESS_TEX, TextureUtil::getHandleIfExist(__pShininessTex));
		materialSetter.setUniformUvec2(Name::Material::ALPHA_TEX, TextureUtil::getHandleIfExist(__pAlphaTex));
		materialSetter.setUniformUvec2(Name::Material::NORMAL_TEX, TextureUtil::getHandleIfExist(__pNormalTex));
	}

	void PhongMaterialComponent::setAmbientTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pAmbientTex = pTexture;
	}

	void PhongMaterialComponent::setDiffuseTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pDiffuseTex = pTexture;
	}

	void PhongMaterialComponent::setSpecularTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pSpecularTex = pTexture;
	}

	void PhongMaterialComponent::setEmissiveTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pEmissiveTex = pTexture;
	}

	void PhongMaterialComponent::setShininess(const float shininess) noexcept
	{
		__shininess = shininess;
	}

	void PhongMaterialComponent::setShininessTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pShininessTex = pTexture;
	}

	void PhongMaterialComponent::setAlphaTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pAlphaTex = pTexture;
	}

	void PhongMaterialComponent::setNormalTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pNormalTex = pTexture;
	}
}