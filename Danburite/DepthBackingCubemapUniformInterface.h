#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class DepthBackingCubemapUniformInterface : public UniformInterface
	{
	public:
		// 64byte * 6
		const UniformField<glm::mat4[6]> projViewMatrices = _appendField<glm::mat4[6]>();

		// 12byte
		const UniformField<glm::vec3> center = _appendField<glm::vec3>();

		// 4byte
		const UniformField<GLfloat> zFar = _appendField<GLfloat>();

		DepthBackingCubemapUniformInterface() noexcept;
		virtual ~DepthBackingCubemapUniformInterface() = default;
	};
}
