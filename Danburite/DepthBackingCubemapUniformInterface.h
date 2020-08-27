#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class DepthBackingCubemapUniformInterface : public UniformInterface
	{
	public:
		const UniformField<glm::mat4[6]> projViewMatrices = _appendField<glm::mat4[6]>();

		DepthBackingCubemapUniformInterface() noexcept;
		virtual ~DepthBackingCubemapUniformInterface() = default;
	};
}
