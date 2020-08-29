#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class DepthBacking2DUniformInterface : public UniformInterface<16ULL>
	{
	public:
		const SpecializedUniformField<glm::mat4> projViewMat = _createField<glm::mat4>(0);

		DepthBacking2DUniformInterface() noexcept;
		virtual ~DepthBacking2DUniformInterface() = default;
	};
}
