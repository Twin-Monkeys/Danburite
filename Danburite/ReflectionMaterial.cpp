#include "ReflectionMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ReflectionMaterial::ReflectionMaterial(const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		Material(MaterialType::REFLECTION, vertexType, uniformSetter),
		_reflectionProgram(ProgramFactory::getInstance().getProgram(ProgramType::REFLECTION))
	{}

	void ReflectionMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		_reflectionProgram.bind();
		vertexArray.draw(numInstances);
	}
}