#include "LightUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	LightUniformInterface::LightUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT }
	{}
}