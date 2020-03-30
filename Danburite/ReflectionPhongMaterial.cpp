#include "ReflectionPhongMaterial.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionPhongMaterial::ReflectionPhongMaterial(const VertexAttributeType vertexType) noexcept :
		Material(MaterialType::REFLECTION_PHONG, vertexType),
		_reflectionPhongProgram(ProgramFactory::getInstance().getProgram(ProgramType::REFLECTION_PHONG))
	{
		useLighting(true);
	}

	void ReflectionPhongMaterial::_onRender(UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.directDeploy(*this);
		materialSetter.setUniformUvec2(ShaderIdentifier::Name::Material::ENVIRONMENT_TEX, TextureUtil::getHandleIfExist(__pEnvTex));

		_reflectionPhongProgram.bind();
		vertexArray.draw(numInstances);
	}

	void ReflectionPhongMaterial::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}
}