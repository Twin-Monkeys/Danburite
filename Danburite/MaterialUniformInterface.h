#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class MaterialUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint> type;
		const UniformField<GLuint> optionFlag;
		const UniformField<GLuint> vertexFlag;

		MaterialUniformInterface() noexcept;
		virtual ~MaterialUniformInterface() = default;
	};
}
