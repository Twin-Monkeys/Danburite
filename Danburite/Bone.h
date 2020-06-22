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

	public:
		Bone(const GLuint id, const std::string &boneNodeName, const glm::mat4 &offsetMatrix) noexcept;

		constexpr const std::string &getNodeName() const noexcept;
		glm::mat4 calcBoneMatrix(const glm::mat4 &nodeMatrix) const noexcept;
	};

	constexpr const std::string &Bone::getNodeName() const noexcept
	{
		return __boneNodeName;
	}
}
