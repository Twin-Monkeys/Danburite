#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class DepthBacking2DUniformInterface : public UniformInterface
	{
	public:
		const UniformField<glm::mat4> projViewMat = _appendField<glm::mat4>();

		DepthBacking2DUniformInterface() noexcept;
		virtual ~DepthBacking2DUniformInterface() = default;
	};
}
