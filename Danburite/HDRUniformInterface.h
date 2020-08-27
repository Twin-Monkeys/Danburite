#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class HDRUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLfloat> exposure = _appendField<GLfloat>();

		HDRUniformInterface() noexcept;
		virtual ~HDRUniformInterface() = default;
	};
}
