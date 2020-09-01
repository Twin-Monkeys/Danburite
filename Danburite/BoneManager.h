#pragma once

#include "Bone.h"
#include "UniformBufferFactory.h"
#include "BoneUniformInterface.h"
#include "Animation.h"
#include "BoneException.h"

namespace Danburite
{
	class BoneManager
	{
	private:
		const JointManager &__jointMgr;
		std::vector<std::unique_ptr<Bone>> __bones;

		DeferredUniformBuffer<BoneUniformInterface> &__boneUB =
			UniformBufferFactory::getInstance().getUniformBuffer<BoneUniformInterface>();

	public:
		BoneManager(const JointManager &jointManager);

		Bone &createBone(
			const std::string& targetNodeName, const std::string& srcNodeName, const glm::mat4 &offsetMatrix);
		
		void updateBones() noexcept;
		void selfDeploy() const noexcept;
	};
}
