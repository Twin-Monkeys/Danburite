#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Object.h"
#include "JointManager.h"

namespace Danburite
{
	class Bone : public ObjectGL::Object<GLuint>
	{
	private:
		const JointManager &__jointMgr;
		const std::string __targetNodeName;
		const std::string __srcNodeName;
		const glm::mat4 __offsetMat;
		
		glm::mat4 __boneMat { 1.f };

	public:
		Bone(
			const GLuint id,
			const JointManager &jointManager,
			const std::string_view &targetNodeName, const std::string_view &srcNodeName,
			const glm::mat4 &offsetMatrix) noexcept;

		void calcMatrix(glm::mat4 &retVal) const noexcept;
	};
}
