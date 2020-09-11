#include "RefractionMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	RefractionMaterial::RefractionMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::REFRACTION, vertexFlag)
	{}

	void RefractionMaterial::_onRender(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB,
		VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__refractionProgram.bind();
		_onRawDrawcall(materialUB, vertexArray, numInstances);
	}

	void RefractionMaterial::_onRawDrawcall(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB,
		VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		MaterialUniformInterface &materialUniformInterface = materialUB.getInterface();
		materialUniformInterface.environmentTex = __pEnvTex->getHandle();

		if (isNormalTextureEnabled())
			materialUniformInterface.normalTex = __pNormalTex->getHandle();

		materialUB.selfDeploy();
		vertexArray.draw(numInstances);
	}

	void RefractionMaterial::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}

	void RefractionMaterial::setNormalTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		enableNormalTexture(pTexture.get());
		__pNormalTex = pTexture;
	}
}