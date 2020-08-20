#include "PhongMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PhongMaterial::PhongMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::PHONG, vertexFlag)
	{
		enableLighting(true);
	}

	void PhongMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__phongProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void PhongMaterial::_onRawDrawcall(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.setUniformFloat(ShaderIdentifier::Name::Material::EMISSIVE_STRENGTH, __emissiveStrength);
		materialSetter.setUniformFloat(ShaderIdentifier::Name::Material::SHININESS, __shininess);

		if (isAmbientTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::AMBIENT_TEX, __pAmbientTex->getHandle());

		if (isDiffuseTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::DIFFUSE_TEX, __pDiffuseTex->getHandle());

		if (isSpecularTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::SPECULAR_TEX, __pSpecularTex->getHandle());

		if (isEmissiveTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::EMISSIVE_TEX, __pEmissiveTex->getHandle());

		if (isShininessTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::SHININESS_TEX, __pShininessTex->getHandle());

		if (isAlphaTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::ALPHA_TEX, __pAlphaTex->getHandle());

		if (isNormalTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::NORMAL_TEX, __pNormalTex->getHandle());

		if (isHeightTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::HEIGHT_TEX, __pHeightTex->getHandle());

		vertexArray.draw(numInstances);
	}

	void PhongMaterial::setAmbientTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableAmbientTexture(pTexture.get());
		__pAmbientTex = pTexture;
	}

	void PhongMaterial::setDiffuseTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableDiffuseTexture(pTexture.get());
		__pDiffuseTex = pTexture;
	}

	void PhongMaterial::setSpecularTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableSpecularTexture(pTexture.get());
		__pSpecularTex = pTexture;
	}

	void PhongMaterial::setEmissiveTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableEmissiveTexture(pTexture.get());
		__pEmissiveTex = pTexture;
	}

	void PhongMaterial::setShininessTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableShininessTexture(pTexture.get());
		__pShininessTex = pTexture;
	}

	void PhongMaterial::setAlphaTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableAlphaTexture(pTexture.get());
		__pAlphaTex = pTexture;
	}

	void PhongMaterial::setNormalTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableNormalTexture(pTexture.get());
		__pNormalTex = pTexture;
	}

	void PhongMaterial::setHeightTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableHeightTexture(pTexture.get());
		__pHeightTex = pTexture;
	}
}