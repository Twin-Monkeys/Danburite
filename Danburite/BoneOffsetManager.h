#pragma once

#include "BoneOffset.h"
#include "UniformBuffer.h"
#include "Animation.h"
#include "BoneException.h"

namespace Danburite
{
	class BoneOffsetManager
	{
	private:
		std::vector<glm::mat4> __boneMatrices;
		std::vector<std::unique_ptr<BoneOffset>> __boneOffsets;

		ObjectGL::UniformBuffer &__boneSetter;

	public:
		BoneOffsetManager();
		BoneOffset &createBoneOffset(const std::string &name, const glm::mat4 &offsetMatrix, const glm::mat4 &hierarchyMatrix);

		BoneOffset &getBoneOffset(const GLuint id) noexcept;
		const BoneOffset &getBoneOffset(const GLuint id) const noexcept;

		GLuint getNumBoneOffsets() const noexcept;

		void updateMatrices(const Animation &animation) noexcept;

		void selfDeploy() const noexcept;
	};
}
