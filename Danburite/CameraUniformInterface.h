#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class CameraUniformInterface : public UniformInterface<144ULL>
	{
	public:
		// 64byte
		const SpecializedUniformField<glm::mat4> viewMat	= _createField<glm::mat4>(0ULL);
		const SpecializedUniformField<glm::mat4> projMat	= _createField<glm::mat4>(64ULL);

		// 12byte
		const SpecializedUniformField<glm::vec3> pos		= _createField<glm::vec3>(132ULL);

		CameraUniformInterface() noexcept;
		virtual ~CameraUniformInterface() = default;
	};
}