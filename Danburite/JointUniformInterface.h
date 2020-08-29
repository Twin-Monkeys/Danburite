#pragma once

#include <glm/glm.hpp>
#include "UniformInterface.h"

namespace Danburite
{
	class JointUniformInterface : public UniformInterface<16ULL>
	{
	public:
		const SpecializedUniformField<glm::mat4> jointMat = _createField<glm::mat4>(0);

		JointUniformInterface() noexcept;
		virtual ~JointUniformInterface() = default;
	};
}
