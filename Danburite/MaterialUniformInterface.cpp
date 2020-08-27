#include "MaterialUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	MaterialUniformInterface::MaterialUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::MATERIAL,
			ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL
		}
	{}
}