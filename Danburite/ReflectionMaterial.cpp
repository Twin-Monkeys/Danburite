#include "ReflectionMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionMaterial::ReflectionMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::REFLECTION, vertexFlag)
	{}

	void ReflectionMaterial::_onRender(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__reflectionProgram.bind();
		_onRawDrawcall(materialUB, vertexArray, numInstances);
	}

	void ReflectionMaterial::_onRawDrawcall(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		MaterialUniformInterface &materialUniformInterface = materialUB.getInterface();
		materialUniformInterface.environmentTex.set(__pEnvTex->getHandle());

		if (isNormalTextureEnabled())
			materialUniformInterface.normalTex.set(__pNormalTex->getHandle());

		materialUB.selfDeploy();
		vertexArray.draw(numInstances);
	}

	void ReflectionMaterial::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}

	void ReflectionMaterial::setNormalTexture(const shared_ptr<Texture2D> &pTexture) noexcept
	{
		__pNormalTex = pTexture;
	}
}