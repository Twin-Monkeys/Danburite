#include "ReflectionMaterial.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionMaterial::ReflectionMaterial(const VertexAttributeType vertexType) noexcept :
		Material({ ProgramType::REFLECTION }, MaterialType::REFLECTION, vertexType)
	{}

	void ReflectionMaterial::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		ReflectionMaterialComponent::_onDeploy(materialSetter);
	}

	void ReflectionMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::REFLECTION).bind();
		vertexArray.draw(numInstances);
	}
}