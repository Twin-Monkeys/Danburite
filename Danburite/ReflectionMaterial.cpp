#include "ReflectionMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionMaterial::ReflectionMaterial(const VertexAttributeType vertexType) noexcept :
		Material(MaterialType::REFLECTION, vertexType),
		_reflectionProgram(ProgramFactory::getInstance().getProgram(ProgramType::REFLECTION))
	{}

	void ReflectionMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.directDeploy(*this);

		_reflectionProgram.bind();
		vertexArray.draw(numInstances);
	}
}