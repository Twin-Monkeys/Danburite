#include "MonoColorMaterial.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	MonoColorMaterial::MonoColorMaterial(const VertexAttributeType vertexType) noexcept :
		Material({ ProgramType::MONO_COLOR }, MaterialType::MONO_COLOR, vertexType)
	{
		useLighting(false);
	}

	void MonoColorMaterial::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		MonoColorMaterialComponent::_onDeploy(materialSetter);
	}

	void MonoColorMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::MONO_COLOR).bind();
		vertexArray.draw(numInstances);
	}
}