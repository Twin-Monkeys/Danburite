#include "LightPrePassUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	LightPrePassUniformInterface::LightPrePassUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT_PREPASS }
	{}
}