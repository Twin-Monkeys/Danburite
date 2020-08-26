#include "TranslucencySwitcherUniformInterface.h"

namespace Danburite
{
	TranslucencySwitcherUniformInterface::TranslucencySwitcherUniformInterface() noexcept :
		mode { _appendField<GLuint, 4>() }
	{}
}