#include "MonoColorMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MonoColorMaterial::MonoColorMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::MONO_COLOR, vertexFlag),
		_monoColorProgram(ProgramFactory::getInstance().getProgram(ProgramType::MONO_COLOR))
	{
		useLighting(false);
	}

	void MonoColorMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_monoColorProgram.bind();
		_onRawDrawcall(materialSetter, vertexArray, numInstances);
	}

	void MonoColorMaterial::_onRawDrawcall(
		UniformSetter& materialSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		_deployMonoColorComponent(materialSetter);
		vertexArray.draw(numInstances);
	}
}