#pragma once

#include <glm/glm.hpp>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class BoneUniformInterface : public UniformInterface<sizeof(glm::mat4) * Constant::Animation::MAX_NUM_BONES>
	{
	public:
		const SpecializedUniformFieldArray<glm::mat4, Constant::Animation::MAX_NUM_BONES>
			boneMatrices = _createFieldArray<glm::mat4, Constant::Animation::MAX_NUM_BONES>(0ULL);

		BoneUniformInterface() noexcept;
		virtual ~BoneUniformInterface() = default;
	};
}
