#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class SkyboxUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint64> albedoTex	= _createField<GLuint64>();
		const UniformField<GLfloat> luminance	= _createField<GLfloat>();

		SkyboxUniformInterface() noexcept;
		virtual ~SkyboxUniformInterface() = default;
	};
}
