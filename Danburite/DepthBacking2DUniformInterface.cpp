#include "DepthBacking2DUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	DepthBacking2DUniformInterface::DepthBacking2DUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::DEPTH_BAKING_2D }
	{}
}