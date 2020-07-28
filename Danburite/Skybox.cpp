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

		__pCubeVA(VertexArrayFactory::createCube(VertexAttributeFlag::POS))
	{}

	void Skybox::draw() noexcept
	{
		_onDraw(__skyBoxSetter, *__pCubeVA);
	}
}