#include "GammaCorrectionUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	GammaCorrectionUniformInterface::GammaCorrectionUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::GAMMA_CORRECTION }
	{}
}