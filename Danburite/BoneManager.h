#pragma once

#include "Bone.h"
#include "UniformBuffer.h"
#include "Animation.h"
#include "BoneException.h"

namespace Danburite
{
	class BoneManager
	{
	private:
		const JointManager &__jointMgr;

		std::vector<glm::mat4> __boneMatrices;
		std::vector<std::unique_ptr<Bone>> __bones;

		ObjectGL::UniformBuffer &__boneSetter;

	public:
		BoneManager(const JointManager &jointManager);

		Bone &createBone(
			const std::string& targetNodeName, const std::string& srcNodeName, const glm::mat4 &offsetMatrix);
		
		void updateBones() noexcept;
		void selfDeploy() const noexcept;
	};
}
