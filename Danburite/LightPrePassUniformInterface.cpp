#include "LightPrePassUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	LightPrePassUniformInterface::LightPrePassUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::LIGHT_PREPASS,
			ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT_PREPASS
		}
	{}
}