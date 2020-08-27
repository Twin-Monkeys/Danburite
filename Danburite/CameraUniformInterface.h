#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class CameraUniformInterface : public UniformInterface
	{
	public:
		// 64byte
		const UniformField<glm::mat4> viewMat	= _appendField<glm::mat4>();
		const UniformField<glm::mat4> projMat	= _appendField<glm::mat4, sizeof(glm::mat4) + 4ULL>();

		// 12byte
		const UniformField<glm::vec3> pos		= _appendField<glm::vec3>();

		CameraUniformInterface() noexcept;
		virtual ~CameraUniformInterface() = default;
	};
}
