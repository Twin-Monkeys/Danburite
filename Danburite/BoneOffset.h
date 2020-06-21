#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Object.h"

namespace Danburite
{
	class BoneOffset : public ObjectGL::Object<GLuint>
	{
	private:
		const std::string __boneName;

		const glm::mat4 __offsetMat;
		const glm::mat4 __hierarchyMat;

	public:
		BoneOffset(
			const GLuint id, const std::string &boneName,
			const glm::mat4 &offsetMatrix, const glm::mat4 &hierarchyMatrix) noexcept;

		constexpr const std::string &getName() const noexcept;

		void calcMatrix(const glm::mat4 &boneMatrix, glm::mat4 &retVal) const noexcept;
	};

	constexpr const std::string &BoneOffset::getName() const noexcept
	{
		return __boneName;
	}
}
