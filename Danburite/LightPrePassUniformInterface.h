#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class LightPrePassUniformInterface : public UniformInterface
	{
	public:
		// 8byte
		const UniformField<GLuint64> ambientTex = _appendField<GLuint64>();
		const UniformField<GLuint64> diffuseTex = _appendField<GLuint64>();
		const UniformField<GLuint64> specularTex = _appendField<GLuint64>();

		// 4byte
		const UniformField<GLuint> lightVolumeType = _appendField<GLuint>();
		const UniformField<GLuint> currentLightIdx = _appendField<GLuint>();

		LightPrePassUniformInterface() noexcept;
		virtual ~LightPrePassUniformInterface() = default;
	};
}
