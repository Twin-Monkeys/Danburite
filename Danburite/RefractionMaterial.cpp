#include "RefractionMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	RefractionMaterial::RefractionMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::REFRACTION, vertexFlag)
	{}

	void RefractionMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__refractionProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void RefractionMaterial::_onRawDrawcall(
		UniformSetter& materialSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::ENVIRONMENT_TEX, __pEnvTex->getHandle());

		if (isNormalTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::NORMAL_TEX, __pNormalTex->getHandle());

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