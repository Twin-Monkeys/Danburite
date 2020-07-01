#pragma once

#include "AnimationManager.h"
#include "JointUpdateObserver.h"
#include <unordered_set>
#include "UniformBuffer.h"

namespace Danburite
{
	class Joint
	{
	private:
		AnimationManager &__animMgr;
		Transform __transform;

		const std::string __nodeName;
		glm::mat4 __jointMat { 1.f };

		std::unordered_set<JointUpdateObserver *> __observerSet;

		ObjectGL::UniformBuffer &__jointSetter;

	public:
		Joint(AnimationManager &animationManager, const std::string_view &nodeName) noexcept;

		constexpr Transform &getTransform() noexcept;
		constexpr const Transform &getTransform() const noexcept;

		Joint &addObserver(JointUpdateObserver *const pObserver) noexcept;

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