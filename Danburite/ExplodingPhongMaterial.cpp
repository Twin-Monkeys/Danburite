#include "ExplodingPhongMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ExplodingPhongMaterial::ExplodingPhongMaterial(const VertexAttributeType vertexType) noexcept :
		Material(MaterialType::EXPLODING_PHONG, vertexType),
		_explodingPhongProgram(ProgramFactory::getInstance().getProgram(ProgramType::EXPLODING_PHONG))
	{
		useLighting(true);
	}

	void ExplodingPhongMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		_deployPhongComponent(materialSetter);

		_explodingPhongProgram.bind();
		vertexArray.draw(numInstances);
	}
}