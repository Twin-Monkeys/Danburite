#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class SkyboxUniformInterface : public UniformInterface<12ULL>
	{
	public:
		const SpecializedUniformField<GLuint64> albedoTex = _createField<GLuint64>(0ULL);
		const SpecializedUniformField<GLfloat> luminance = _createField<GLfloat>(8ULL);

		SkyboxUniformInterface() noexcept;
		virtual ~SkyboxUniformInterface() = default;
	};
}
