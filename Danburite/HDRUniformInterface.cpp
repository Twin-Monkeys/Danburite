#include "HDRUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	HDRUniformInterface::HDRUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::HDR }
	{}
}