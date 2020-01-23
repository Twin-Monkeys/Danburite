#include "ReflectionPhongMaterial.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionPhongMaterial::ReflectionPhongMaterial(const VertexAttributeType vertexType) noexcept :
		PhongMaterial({ ProgramType::REFLECTION_PHONG }, MaterialType::REFLECTION_PHONG, vertexType)
	{
		useLighting(true);
	}

	void ReflectionPhongMaterial::_onDeploy(MaterialUniformSetter &materialUniformSetter) noexcept
	{
		PhongMaterial::_onDeploy(materialUniformSetter);

		if (__pEnvTex)
			__pEnvTex->bind(ShaderIdentifier::Value::Material::ENVIRONMENT_TEX_LOCATION);
	}

	void ReflectionPhongMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::REFLECTION_PHONG).bind();
		vertexArray.draw(numInstances);
	}

	void ReflectionPhongMaterial::setEnvironmentTexture(const shared_ptr<TextureCubemap> &pTexture) noexcept
	{
		__pEnvTex = pTexture;
	}
}