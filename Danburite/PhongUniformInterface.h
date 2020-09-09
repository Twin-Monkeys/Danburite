#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"

namespace Danburite
{
	class PhongUniformInterface : public UniformInterface<16ULL>
	{
	public:
		const SpecializedUniformField<GLuint> calcMethodType = _createField<GLuint>(0ULL);

		PhongUniformInterface() noexcept;
		virtual ~PhongUniformInterface() = default;
	};
}
