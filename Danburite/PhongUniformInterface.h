#pragma once

#include <GL/glew.h>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class PhongUniformInterface : public UniformInterface
	{
	public:
		const UniformField<GLuint> calcMethodType = _appendField<GLuint>();

		PhongUniformInterface() noexcept;
		virtual ~PhongUniformInterface() = default;
	};
}
