#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class GammaCorrectionUniformInterface : public UniformInterface<16ULL>
	{
	public:
		const SpecializedUniformField<GLfloat> gamma = _createField<GLfloat>(0);

		GammaCorrectionUniformInterface() noexcept;
		virtual ~GammaCorrectionUniformInterface() = default;
	};
}
