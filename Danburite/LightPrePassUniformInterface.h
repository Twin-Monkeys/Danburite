#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class LightPrePassUniformInterface : public UniformInterface<96ULL>
	{
	public:
		const SpecializedUniformField<GLuint64> ambientTex		= _createField<GLuint64>(0ULL);
		const SpecializedUniformField<GLuint64> diffuseTex		= _createField<GLuint64>(16ULL);
		const SpecializedUniformField<GLuint64> specularTex		= _createField<GLuint64>(32ULL);
		const SpecializedUniformField<GLuint> lightVolumeType	= _createField<GLuint>(48ULL);
		const SpecializedUniformField<GLuint> currentLightIdx	= _createField<GLuint>(64ULL);
		const SpecializedUniformField<GLuint> ssaoEnabled		= _createField<GLuint>(80ULL);

		LightPrePassUniformInterface() noexcept;
		virtual ~LightPrePassUniformInterface() = default;
	};
}
