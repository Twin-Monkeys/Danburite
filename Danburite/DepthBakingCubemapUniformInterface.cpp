#include "DepthBakingCubemapUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	DepthBakingCubemapUniformInterface::DepthBakingCubemapUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::DEPTH_BAKING_CUBEMAP }
	{}
}