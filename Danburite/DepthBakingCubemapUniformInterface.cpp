#include "DepthBakingCubemapUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	DepthBakingCubemapUniformInterface::DepthBakingCubemapUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_CUBEMAP,
			ShaderIdentifier::Value::UniformBlockBindingPoint::DEPTH_BAKING_CUBEMAP
		}
	{}
}