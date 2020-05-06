#include "ReflectionMaterial.h"
#include "ProgramFactory.h"

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
		_deployReflectionComponent(materialSetter);

		_reflectionProgram.bind();
		vertexArray.draw(numInstances);
	}
}