#pragma once

#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class JointUniformInterface : public UniformInterface
	{
	public:
		const UniformField<glm::mat4> jointMat = _appendField<glm::mat4>();

		JointUniformInterface() noexcept;
		virtual ~JointUniformInterface() = default;
	};
}
