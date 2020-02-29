#include "PhongMaterialComponent.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void PhongMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		materialSetter.traverseProgram(
			&Program::setUniformFloat, ShaderIdentifier::Name::Material::SHININESS, __shininess);

		TextureUtil::bindIfExist(__pAmbientTex, ShaderIdentifier::Value::Material::AMBIENT_TEX_LOCATION);
		TextureUtil::bindIfExist(__pDiffuseTex, ShaderIdentifier::Value::Material::DIFFUSE_TEX_LOCATION);
		TextureUtil::bindIfExist(__pSpecularTex, ShaderIdentifier::Value::Material::SPECULAR_TEX_LOCATION);
		TextureUtil::bindIfExist(__pEmissiveTex, ShaderIdentifier::Value::Material::EMISSIVE_TEX_LOCATION);
		TextureUtil::bindIfExist(__pShininessTex, ShaderIdentifier::Value::Material::SHININESS_TEX_LOCATION);
		TextureUtil::bindIfExist(__pAlphaTex, ShaderIdentifier::Value::Material::ALPHA_TEX_LOCATION);
		TextureUtil::bindIfExist(__pNormalTex, ShaderIdentifier::Value::Material::NORMAL_TEX_LOCATION);

		if (__pDiffuseTex)
		{
			if (!__pDiffuseTex->getHandle())
				__pDiffuseTex->createHandle();

			materialSetter.getProgram(ProgramType::PHONG).
				setUniformUvec2("material.diffuseHandle", __pDiffuseTex->getHandle());
		}
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