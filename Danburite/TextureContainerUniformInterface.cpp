#include "TextureContainerUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	TextureContainerUniformInterface::TextureContainerUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::TEX_CONTAINER }
	{}
}