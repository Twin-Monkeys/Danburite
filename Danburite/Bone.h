#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Object.h"

namespace Danburite
{
	class Bone : public ObjectGL::Object<GLuint>
	{
	private:
		const std::string __name;

		const glm::mat4 __offsetMat;
		const glm::mat4 __offsetInvMat;

	public:
		Bone(const GLuint id, const std::string &name, const glm::mat4 &offsetMatrix) noexcept;

		constexpr const std::string &getName() const noexcept;

		void calcBoneMatrix(const glm::mat4 &nodeMatrix, glm::mat4 &retVal) const noexcept;
	};

	constexpr const std::string &Bone::getName() const noexcept
	{
		return __name;
	}
}
