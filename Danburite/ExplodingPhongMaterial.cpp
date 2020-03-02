#include "ExplodingPhongMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ExplodingPhongMaterial::ExplodingPhongMaterial(
		const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		Material(MaterialType::EXPLODING_PHONG, vertexType, uniformSetter),
		_explodingPhongProgram(ProgramFactory::getInstance().getProgram(ProgramType::EXPLODING_PHONG))
	{
		useLighting(true);
	}

	void ExplodingPhongMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		_explodingPhongProgram.bind();
		vertexArray.draw(numInstances);
	}
}