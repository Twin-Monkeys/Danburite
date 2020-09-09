#include "MaterialUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	MaterialUniformInterface::MaterialUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL }
	{}
}