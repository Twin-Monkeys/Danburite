#include "HDRUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	HDRUniformInterface::HDRUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::HDR,
			ShaderIdentifier::Value::UniformBlockBindingPoint::HDR
		}
	{}
}