#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class HDRUniformInterface : public UniformInterface<4ULL>
	{
	public:
		const SpecializedUniformField<GLfloat> exposure = _createField<GLfloat>(0);

		HDRUniformInterface() noexcept;
		virtual ~HDRUniformInterface() = default;
	};
}
