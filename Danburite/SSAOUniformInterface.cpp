#include "SSAOUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	SSAOUniformInterface::SSAOUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::SSAO }
	{}
}