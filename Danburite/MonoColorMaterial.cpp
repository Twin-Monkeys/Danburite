#include "MonoColorMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MonoColorMaterial::MonoColorMaterial(const VertexAttributeType vertexType) noexcept :
		Material(MaterialType::MONO_COLOR, vertexType),
		_monoColorProgram(ProgramFactory::getInstance().getProgram(ProgramType::MONO_COLOR))
	{
		useLighting(false);
	}

	void MonoColorMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		materialSetter.directDeploy(*this);

		_monoColorProgram.bind();
		vertexArray.draw(numInstances);
	}
}