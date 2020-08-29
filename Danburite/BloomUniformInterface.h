#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class BloomUniformInterface : public UniformInterface<8ULL>
	{
	public:
		// 4byte
		const SpecializedUniformField<GLfloat> brightnessThreshold	= _createField<GLfloat>(0ULL);
		const SpecializedUniformField<GLfloat> effectStrength		= _createField<GLfloat>(4ULL);

		BloomUniformInterface() noexcept;
		virtual ~BloomUniformInterface() = default;
	};
}
