#include "ReflectionMaterial.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionMaterial::ReflectionMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::REFLECTION, vertexFlag),
		_reflectionProgram(ProgramFactory::getInstance().getProgram(ProgramType::REFLECTION))
	{}

	void ReflectionMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_reflectionProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void ReflectionMaterial::_onRawDrawcall(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::ENVIRONMENT_TEX, __pEnvTex->getHandle());

		if (isNormalTextureEnabled())
			materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::NORMAL_TEX, __pNormalTex->getHandle());

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