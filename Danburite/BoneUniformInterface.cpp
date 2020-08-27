#include "BoneUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	BoneUniformInterface::BoneUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::BONE,
			ShaderIdentifier::Value::UniformBlockBindingPoint::BONE
		}
	{}
}