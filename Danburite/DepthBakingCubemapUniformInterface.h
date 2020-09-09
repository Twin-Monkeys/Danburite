#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class DepthBakingCubemapUniformInterface : public UniformInterface<416ULL>
	{
	public:
		const SpecializedUniformFieldArray<glm::mat4, 6ULL> projViewMatrices =
			_createFieldArray<glm::mat4, 6ULL>(0);

		const SpecializedUniformField<glm::vec3> center	= _createField<glm::vec3>(384ULL);
		const SpecializedUniformField<GLfloat> zFar		= _createField<GLfloat>(400ULL);

		DepthBakingCubemapUniformInterface() noexcept;
		virtual ~DepthBakingCubemapUniformInterface() = default;
	};
}
