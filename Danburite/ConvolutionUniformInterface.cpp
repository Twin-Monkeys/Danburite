#include "ConvolutionUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	ConvolutionUniformInterface::ConvolutionUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::CONVOLUTION }
	{}
}