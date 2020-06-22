#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Object.h"

namespace Danburite
{
	class Bone : public ObjectGL::Object<GLuint>
	{
	private:
		const std::string __boneNodeName;

		const glm::mat4 __offsetMat;
		const glm::mat4 __hierarchyMat;

	public:
		Bone(
			const GLuint id, const std::string &boneNodeName,
			const glm::mat4 &offsetMatrix, const glm::mat4 &hierarchyMatrix) noexcept;

		constexpr const std::string &getNodeName() const noexcept;
		void calcBoneMatrix(const glm::mat4 &nodeMatrix, glm::mat4 &retVal) const noexcept;
	};

	constexpr const std::string &Bone::getNodeName() const noexcept
	{
		return __boneNodeName;
	}
}
