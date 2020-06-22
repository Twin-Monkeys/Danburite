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
		std::vector<std::unique_ptr<Bone>> __boneOffsets;

		ObjectGL::UniformBuffer &__boneSetter;

	public:
		BoneOffsetManager();
		Bone &createBoneOffset(const std::string &name, const glm::mat4 &offsetMatrix, const glm::mat4 &hierarchyMatrix);

		Bone &getBoneOffset(const GLuint id) noexcept;
		const Bone &getBoneOffset(const GLuint id) const noexcept;

		GLuint getNumBoneOffsets() const noexcept;

		void updateMatrices(const Animation &animation) noexcept;

		void selfDeploy() const noexcept;
	};
}
