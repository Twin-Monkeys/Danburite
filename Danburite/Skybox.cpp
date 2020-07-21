#include "Skybox.h"
#include "VertexArrayFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Skybox::Skybox() noexcept :
		__skyBoxSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::SKYBOX)),

		__pCubeVA(VertexArrayFactory::createInstance(ShapeType::CUBE, VertexAttributeFlag::POS))
	{}

	void Skybox::draw() noexcept
	{
		_onDraw(__skyBoxSetter);
	}

	void Skybox::_drawBoxVA() noexcept
	{
		__pCubeVA->draw();
	}
}