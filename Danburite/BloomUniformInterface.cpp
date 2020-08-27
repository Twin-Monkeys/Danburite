#include "BloomUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	BloomUniformInterface::BloomUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::BLOOM,
			ShaderIdentifier::Value::UniformBlockBindingPoint::BLOOM
		}
	{}
}