#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Object.h"
#include <vector>

namespace Danburite
{
	class Bone : public ObjectGL::Object<GLuint>
	{
	private:
		const glm::mat4 __offsetMat;
		const glm::mat4 __offsetInvMat;

		std::vector<glm::mat4> &__boneMatrices;

		void __setboneMatrix(const glm::mat4 &boneMatrix) const noexcept;

	public:
		Bone(const GLuint id, const glm::mat4 &offsetMatrix, std::vector<glm::mat4> &boneMatricesRef) noexcept;
		void updateMatrix(const glm::mat4 &nodeMatrix) noexcept;
	};
}
