#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Object.h"

namespace Danburite
{
	class Bone : public ObjectGL::Object<GLuint>
	{
	private:
		const glm::mat4 __offsetMat;
		
		glm::mat4 __targetJointMat	{ 1.f };
		glm::mat4 __srcJointMat		{ 1.f };
		glm::mat4 __boneMat			{ 1.f };

	public:
		Bone(const GLuint id, const glm::mat4 &offsetMatrix) noexcept;

		constexpr const glm::mat4 &getTargetJointMatrix() const noexcept;
		constexpr void setTargetJointMatrix(const glm::mat4 &jointMatrix) noexcept;

		constexpr const glm::mat4 &getSourceJointMatrix() const noexcept;
		constexpr void setSourceJointMatrix(const glm::mat4 &jointMatrix) noexcept;

		void updateMatrix() noexcept;
		constexpr const glm::mat4 &getMatrix() const noexcept;
	};

	constexpr const glm::mat4 &Bone::getTargetJointMatrix() const noexcept
	{
		return __targetJointMat;
	}

	constexpr void Bone::setTargetJointMatrix(const glm::mat4 &jointMatrix) noexcept
	{
		__targetJointMat = jointMatrix;
	}

	constexpr const glm::mat4 &Bone::getSourceJointMatrix() const noexcept
	{
		return __srcJointMat;
	}

	constexpr void Bone::setSourceJointMatrix(const glm::mat4 &jointMatrix) noexcept
	{
		__srcJointMat = jointMatrix;
	}

	constexpr const glm::mat4 &Bone::getMatrix() const noexcept
	{
		return __boneMat;
	}
}
