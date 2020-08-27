#include "TextureContainerUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	TextureContainerUniformInterface::TextureContainerUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER,
			ShaderIdentifier::Value::UniformBlockBindingPoint::TEX_CONTAINER
		}
	{}
}