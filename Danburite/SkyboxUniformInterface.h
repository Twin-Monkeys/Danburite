#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class SkyboxUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint64> albedoTex	= _appendField<GLuint64>();
		const UniformField<GLfloat> luminance	= _appendField<GLfloat>();

		SkyboxUniformInterface() noexcept;
		virtual ~SkyboxUniformInterface() = default;
	};
}
