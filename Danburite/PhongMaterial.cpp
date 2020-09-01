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

		materialUniformInterface.emissiveStrength.set(__emissiveStrength);
		materialUniformInterface.shininess.set(__shininess);

		if (isAmbientTextureEnabled())
			materialUniformInterface.ambientTex.set(__pAmbientTex->getHandle());

		if (isDiffuseTextureEnabled())
			materialUniformInterface.diffuseTex.set(__pDiffuseTex->getHandle());

		if (isSpecularTextureEnabled())
			materialUniformInterface.specularTex.set(__pSpecularTex->getHandle());

		if (isEmissiveTextureEnabled())
			materialUniformInterface.emissiveTex.set(__pEmissiveTex->getHandle());

		if (isShininessTextureEnabled())
			materialUniformInterface.shininessTex.set(__pShininessTex->getHandle());

		if (isAlphaTextureEnabled())
			materialUniformInterface.alphaTex.set(__pAlphaTex->getHandle());

		if (isNormalTextureEnabled())
			materialUniformInterface.normalTex.set(__pNormalTex->getHandle());

		if (isHeightTextureEnabled())
			materialUniformInterface.heightTex.set(__pHeightTex->getHandle());

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
}