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
		const UniformField<GLuint64> ambientTex = _createField<GLuint64>();
		const UniformField<GLuint64> diffuseTex = _createField<GLuint64>();
		const UniformField<GLuint64> specularTex = _createField<GLuint64>();

		// 4byte
		const UniformField<GLuint> lightVolumeType = _createField<GLuint>();
		const UniformField<GLuint> currentLightIdx = _createField<GLuint>();

		LightPrePassUniformInterface() noexcept;
		virtual ~LightPrePassUniformInterface() = default;
	};
}
