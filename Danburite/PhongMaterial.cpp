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
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__phongProgram.bind();
		_onRawDrawcall(materialUB, vertexArray, numInstances);
	}

	void PhongMaterial::_onRawDrawcall(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		MaterialUniformInterface &materialUniformInterface = materialUB.getInterface();

		materialUniformInterface.emissiveStrength = __emissiveStrength;
		materialUniformInterface.shininess = __shininess;

		if (isAmbientTextureEnabled())
			materialUniformInterface.ambientTex = __pAmbientTex->getHandle();

		if (isDiffuseTextureEnabled())
			materialUniformInterface.diffuseTex = __pDiffuseTex->getHandle();

		if (isSpecularTextureEnabled())
			materialUniformInterface.specularTex = __pSpecularTex->getHandle();

		if (isEmissiveTextureEnabled())
			materialUniformInterface.emissiveTex = __pEmissiveTex->getHandle();

		if (isShininessTextureEnabled())
			materialUniformInterface.shininessTex = __pShininessTex->getHandle();

		if (isAlphaTextureEnabled())
			materialUniformInterface.alphaTex = __pAlphaTex->getHandle();

		if (isNormalTextureEnabled())
			materialUniformInterface.normalTex = __pNormalTex->getHandle();

		if (isHeightTextureEnabled())
			materialUniformInterface.heightTex = __pHeightTex->getHandle();

		if (isOcclusionTextureEnabled())
			materialUniformInterface.occlusionTex = __pOcclusionTex->getHandle();

		materialUB.selfDeploy();
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

	void PhongMaterial::setOcclusionTexture(const std::shared_ptr<ObjectGL::Texture2D>& pTexture) noexcept
	{
		enableOcclusionTexture(pTexture.get());
		__pOcclusionTex = pTexture;
	}
}