#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class BloomUniformInterface : public UniformInterface
	{
	public:
		// 4byte
		const UniformField<GLfloat> brightnessThreshold = _appendField<GLfloat>();
		const UniformField<GLfloat> effectStrength = _appendField<GLfloat>();

		BloomUniformInterface() noexcept;
		virtual ~BloomUniformInterface() = default;
	};
}
