#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class BloomUniformInterface : public UniformInterface<32ULL>
	{
	public:
		const SpecializedUniformField<GLfloat> brightnessThreshold	= _createField<GLfloat>(0ULL);
		const SpecializedUniformField<GLfloat> effectStrength		= _createField<GLfloat>(16ULL);

		BloomUniformInterface() noexcept;
		virtual ~BloomUniformInterface() = default;
	};
}
