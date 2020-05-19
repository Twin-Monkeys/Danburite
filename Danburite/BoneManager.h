#pragma once

#include <vector>
#include "Bone.h"
#include "UniformBuffer.h"
#include "BoneException.h"

namespace Danburite
{
	class BoneManager
	{
	private:
		std::vector<glm::mat4> __boneMatrices;
		std::vector<std::unique_ptr<Bone>> __bones;

		ObjectGL::UniformBuffer &__boneSetter;

	public:
		BoneManager();
		Bone &createBone(const glm::mat4 &offsetMatrix);

		Bone &getBone(const GLuint id) noexcept;
		const Bone &getBone(const GLuint id) const noexcept;

		GLuint getNumBones() const noexcept;

		void updateMatrics(const glm::mat4 &nodeMatrix) noexcept;

		void selfDeploy() const noexcept;
	};
}
