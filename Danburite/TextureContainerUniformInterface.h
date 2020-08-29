#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class TextureContainerUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint64[Constant::TextureContainer::MAX_TEXTURE_CONTAINER_ELEMS]> textures =
			_createField<GLuint64[Constant::TextureContainer::MAX_TEXTURE_CONTAINER_ELEMS]>();

		TextureContainerUniformInterface() noexcept;
		virtual ~TextureContainerUniformInterface() = default;
	};
}
