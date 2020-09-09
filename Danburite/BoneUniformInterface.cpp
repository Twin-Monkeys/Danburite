#include "BoneUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	BoneUniformInterface::BoneUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::BONE }
	{}
}