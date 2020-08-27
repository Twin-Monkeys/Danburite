#include "DepthBackingCubemapUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	DepthBackingCubemapUniformInterface::DepthBackingCubemapUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_CUBEMAP,
			ShaderIdentifier::Value::UniformBlockBindingPoint::DEPTH_BAKING_CUBEMAP
		}
	{}
}