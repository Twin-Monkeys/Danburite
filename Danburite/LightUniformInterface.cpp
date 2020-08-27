#include "LightUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	LightUniformInterface::LightUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::LIGHT,
			ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT
		}
	{}
}