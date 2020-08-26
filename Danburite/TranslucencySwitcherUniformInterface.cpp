#include "TranslucencySwitcherUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	TranslucencySwitcherUniformInterface::TranslucencySwitcherUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::TRANSLUCENCY_SWITCHER,
			ShaderIdentifier::Value::UniformBlockBindingPoint::TRANSLUCENCY_SWITCHER
		},
		mode { _appendField<GLuint, 4>() }
	{}
}