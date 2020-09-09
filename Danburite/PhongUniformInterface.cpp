#include "PhongUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	PhongUniformInterface::PhongUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::PHONG }
	{}
}