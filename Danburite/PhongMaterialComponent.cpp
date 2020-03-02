#include "PhongMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"
#include "UniformSetter.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void PhongMaterialComponent::_onDeploy(UniformSetter &uniformSetter) noexcept
	{
		uniformSetter.setUniformFloat(ShaderIdentifier::Name::Material::SHININESS, __shininess);
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::AMBIENT_TEX, TextureUtil::getHandleIfExist(__pAmbientTex));
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::DIFFUSE_TEX, TextureUtil::getHandleIfExist(__pDiffuseTex));
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::SPECULAR_TEX, TextureUtil::getHandleIfExist(__pSpecularTex));
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::EMISSIVE_TEX, TextureUtil::getHandleIfExist(__pEmissiveTex));
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::SHININESS_TEX, TextureUtil::getHandleIfExist(__pShininessTex));
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::ALPHA_TEX, TextureUtil::getHandleIfExist(__pAlphaTex));
		uniformSetter.setUniformUvec2(ShaderIdentifier::Name::Material::NORMAL_TEX, TextureUtil::getHandleIfExist(__pNormalTex));
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