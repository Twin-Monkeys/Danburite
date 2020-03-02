#include "Skybox.h"
#include "ProgramFactory.h"
#include "VertexArrayFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Skybox::Skybox(UniformSetter &uniformSetter) noexcept :
		__uniformSetter(uniformSetter)
	{}

	void Skybox::draw() noexcept
	{
		_onDraw(__uniformSetter);
	}

	void Skybox::_drawBoxVA() noexcept
	{
		VertexArray &cubeVA =
			VertexArrayFactory::getInstance().getVertexArrayReference(ShapeType::CUBE, VertexAttributeType::POS3);

		cubeVA.draw();
	}
}