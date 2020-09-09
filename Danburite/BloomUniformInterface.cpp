#include "BloomUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	BloomUniformInterface::BloomUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::BLOOM }
	{}
}