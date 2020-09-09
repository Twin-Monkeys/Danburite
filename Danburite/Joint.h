#pragma once

#include "AnimationManager.h"
#include "UniformBufferFactory.h"
#include "JointUniformInterface.h"

namespace Danburite
{
	class Joint
	{
	private:
		AnimationManager &__animMgr;
		Transform __transform;

		const std::string __nodeName;
		glm::mat4 __jointMat { 1.f };

		DeferredUniformBuffer<JointUniformInterface> &__jointUB =
			UniformBufferFactory::getInstance().getUniformBuffer<JointUniformInterface>();

	public:
		Joint(AnimationManager &animationManager, const std::string_view &nodeName) noexcept;

		constexpr Transform &getTransform() noexcept;
		constexpr const Transform &getTransform() const noexcept;

		Joint &updateMatrix(const glm::mat4 &parentJointMatrix) noexcept;
		constexpr const glm::mat4 &getMatrix() const noexcept;

		void selfDeploy() const noexcept;
	};

	constexpr Transform &Joint::getTransform() noexcept
	{
		return __transform;
	}

	constexpr const Transform &Joint::getTransform() const noexcept
	{
		return __transform;
	}

	constexpr const glm::mat4 &Joint::getMatrix() const noexcept
	{
		return __jointMat;
	}
}