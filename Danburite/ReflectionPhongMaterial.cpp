#include "ReflectionPhongMaterial.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionPhongMaterial::ReflectionPhongMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::REFLECTION_PHONG, vertexFlag),
		_reflectionPhongProgram(ProgramFactory::getInstance().getProgram(ProgramType::REFLECTION_PHONG))
	{
		useLighting(true);
	}

	void ReflectionPhongMaterial::_onRender(UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_reflectionPhongProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void ReflectionPhongMaterial::_onRawDrawcall(
		UniformSetter& materialSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		_deployPhongComponent(materialSetter);
		materialSetter.setUniformUvec2(
			ShaderIdentifier::Name::Material::ENVIRONMENT_TEX, TextureUtil::getHandleIfExist(__pEnvTex));

		vertexArray.draw(numInstances);
	}

	void ReflectionPhongMaterial::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}
}