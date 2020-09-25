#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class SSAOUniformInterface : public UniformInterface<64ULL>
	{
	public:
		const SpecializedUniformField<GLfloat> samplingRadius = _createField<GLfloat>(0ULL);
		const SpecializedUniformField<GLfloat> strength = _createField<GLfloat>(16ULL);
		const SpecializedUniformField<GLuint> numSamples = _createField<GLuint>(32ULL);
		const SpecializedUniformField<GLuint> blurRange = _createField<GLuint>(48ULL);

		SSAOUniformInterface() noexcept;
		virtual ~SSAOUniformInterface() = default;
	};
}
