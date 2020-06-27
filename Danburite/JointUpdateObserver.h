#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Danburite
{
	class JointUpdateObserver abstract
	{
	public:
		virtual void onUpdateJointMatrix(
			const std::string &jointName, const glm::mat4 &jointMatrix) noexcept = 0;
	};
}
