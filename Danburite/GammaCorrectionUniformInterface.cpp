#include "GammaCorrectionUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	GammaCorrectionUniformInterface::GammaCorrectionUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION,
			ShaderIdentifier::Value::UniformBlockBindingPoint::GAMMA_CORRECTION
		}
	{}
}