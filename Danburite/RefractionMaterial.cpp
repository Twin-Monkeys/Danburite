#include "RefractionMaterial.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	RefractionMaterial::RefractionMaterial(const VertexAttributeType vertexType) noexcept :
		Material({ ProgramType::REFRACTION }, MaterialType::REFRACTION, vertexType)
	{}

	void RefractionMaterial::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		RefractionMaterialComponent::_onDeploy(materialSetter);
	}

	void RefractionMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::REFRACTION).bind();
		vertexArray.draw(numInstances);
	}
}