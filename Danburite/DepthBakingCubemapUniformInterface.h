#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class DepthBakingCubemapUniformInterface : public UniformInterface<400ULL>
	{
	public:
		// 64byte * 6
		const SpecializedUniformFieldArray<glm::mat4, 6ULL> projViewMatrices =
			_createFieldArray<glm::mat4, 6ULL>(0);

		// 12byte
		const SpecializedUniformField<glm::vec3> center = _createField<glm::vec3>(384ULL);

		// 4byte
		const SpecializedUniformField<GLfloat> zFar = _createField<GLfloat>(396ULL);

		DepthBakingCubemapUniformInterface() noexcept;
		virtual ~DepthBakingCubemapUniformInterface() = default;
	};
}
