#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class TextureContainerUniformInterface : public UniformInterface<
		sizeof(GLuint64) * Constant::TextureContainer::MAX_TEXTURE_CONTAINER_ELEMS>
	{
	public:
		const SpecializedUniformFieldArray<
			GLuint64, Constant::TextureContainer::MAX_TEXTURE_CONTAINER_ELEMS>
			textures = _createFieldArray<GLuint64, Constant::TextureContainer::MAX_TEXTURE_CONTAINER_ELEMS>
			(0);

		TextureContainerUniformInterface() noexcept;
		virtual ~TextureContainerUniformInterface() = default;
	};
}
