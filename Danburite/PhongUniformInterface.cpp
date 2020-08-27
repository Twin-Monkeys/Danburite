#include "PhongUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	PhongUniformInterface::PhongUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::PHONG,
			ShaderIdentifier::Value::UniformBlockBindingPoint::PHONG
		}
	{}
}