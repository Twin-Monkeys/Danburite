#include "JointUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	JointUniformInterface::JointUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::JOINT,
			ShaderIdentifier::Value::UniformBlockBindingPoint::JOINT
		}
	{}
}