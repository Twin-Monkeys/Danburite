#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class TranslucencySwitcherUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint> mode = _appendField<GLuint>();

		TranslucencySwitcherUniformInterface() noexcept;
		virtual ~TranslucencySwitcherUniformInterface() = default;
	};
}
