#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class LightPrePassUniformInterface : public UniformInterface<32ULL>
	{
	public:
		// 8byte
		const SpecializedUniformField<GLuint64> ambientTex = _createField<GLuint64>(0ULL);
		const SpecializedUniformField<GLuint64> diffuseTex = _createField<GLuint64>(8ULL);
		const SpecializedUniformField<GLuint64> specularTex = _createField<GLuint64>(16ULL);

		// 4byte
		const SpecializedUniformField<GLuint> lightVolumeType = _createField<GLuint>(24ULL);
		const SpecializedUniformField<GLuint> currentLightIdx = _createField<GLuint>(28ULL);

		LightPrePassUniformInterface() noexcept;
		virtual ~LightPrePassUniformInterface() = default;
	};
}
