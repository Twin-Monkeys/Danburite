#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class GammaCorrectionUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLfloat> gamma = _appendField<GLfloat>();

		GammaCorrectionUniformInterface() noexcept;
		virtual ~GammaCorrectionUniformInterface() = default;
	};
}
