#include "MonoColorMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MonoColorMaterial::MonoColorMaterial(
		const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		Material(MaterialType::MONO_COLOR, vertexType, uniformSetter),
		_monoColorProgram(ProgramFactory::getInstance().getProgram(ProgramType::MONO_COLOR))
	{
		useLighting(false);
	}

	void MonoColorMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		_monoColorProgram.bind();
		vertexArray.draw(numInstances);
	}
}