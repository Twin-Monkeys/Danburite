#include "PhongMaterial.h"
#include "ShaderIdentifier.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PhongMaterial::PhongMaterial(
		const unordered_set<ProgramType> &programTypes,
		const MaterialType type, const VertexAttributeType vertexType) noexcept :
		Material(programTypes, type, vertexType)
	{
		useLighting(true);
	}

	PhongMaterial::PhongMaterial(const VertexAttributeType vertexType) noexcept :
		PhongMaterial({ ProgramType::PHONG }, MaterialType::PHONG, vertexType)
	{}

	void PhongMaterial::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		PhongMaterialComponent::_onDeploy(materialSetter);
	}

	void PhongMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::PHONG).bind();
		vertexArray.draw(numInstances);
	}
}