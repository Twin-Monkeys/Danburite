#include "TranslucencySwitcherUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	TranslucencySwitcherUniformInterface::TranslucencySwitcherUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::TRANSLUCENCY_SWITCHER }
	{}
}