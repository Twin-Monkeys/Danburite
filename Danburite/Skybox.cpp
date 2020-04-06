#include "Skybox.h"
#include "VertexArrayFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Skybox::Skybox() noexcept :
		__skyBoxSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Value::UniformBlockBindingPoint::SKYBOX))
	{}

	void Skybox::draw() noexcept
	{
		_onDraw(__skyBoxSetter);
	}

	void Skybox::_drawBoxVA() noexcept
	{
		VertexArray &cubeVA =
			VertexArrayFactory::getInstance().getVertexArrayReference(ShapeType::CUBE, VertexAttributeType::POS3);

		cubeVA.draw();
	}
}