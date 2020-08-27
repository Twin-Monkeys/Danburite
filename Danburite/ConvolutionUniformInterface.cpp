#include "ConvolutionUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	ConvolutionUniformInterface::ConvolutionUniformInterface() noexcept :
		UniformInterface
	{
		ShaderIdentifier::Name::UniformBuffer::CONVOLUTION,
		ShaderIdentifier::Value::UniformBlockBindingPoint::CONVOLUTION
	}
	{}
}