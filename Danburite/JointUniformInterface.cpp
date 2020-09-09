#include "JointUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	JointUniformInterface::JointUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::JOINT }
	{}
}