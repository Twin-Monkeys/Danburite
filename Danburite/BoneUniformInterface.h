#pragma once

#include <glm/glm.hpp>
#include "UniformInterface.h"
#include "Constant.h"

namespace Danburite
{
	class BoneUniformInterface : public UniformInterface
	{
	public:
		const UniformField<glm::mat4[Constant::Animation::MAX_NUM_BONES]> boneMatrices =
			_appendField<glm::mat4[Constant::Animation::MAX_NUM_BONES]>();

		BoneUniformInterface() noexcept;
		virtual ~BoneUniformInterface() = default;
	};
}
