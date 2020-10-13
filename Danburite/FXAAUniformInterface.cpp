#include "FXAAUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	FXAAUniformInterface::FXAAUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::FXAA }
	{}
}