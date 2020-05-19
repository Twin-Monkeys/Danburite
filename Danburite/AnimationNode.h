#pragma once

#include "TransformTimeline.h"
#include "Transform.h"
#include <unordered_set>
#include "Constant.h"
#include "Bone.h"

namespace Danburite
{
	class AnimationNode
	{
	private:
		TransformTimeline __timeline;
		const float &__timestamp;

		Transform __currentTransform;
		glm::mat4 __nodeMat;

		void __updateTransform(const float timestamp) noexcept;

	public:
		explicit constexpr AnimationNode(const float &timestampReference) noexcept;

		constexpr TransformTimeline &getTimeline() noexcept;
		constexpr const TransformTimeline &getTimeline() const noexcept;

		void updateMatrix() noexcept;
		void updateMatrix(const glm::mat4 &parentMatrix) noexcept;

		constexpr const glm::mat4 &getNodeMatrix() const noexcept;
	};

	constexpr AnimationNode::AnimationNode(const float &timestampReference) noexcept :
		__timestamp(timestampReference)
	{}

	constexpr TransformTimeline &AnimationNode::getTimeline() noexcept
	{
		return __timeline;
	}

	constexpr const TransformTimeline &AnimationNode::getTimeline() const noexcept
	{
		return __timeline;
	}

	constexpr const glm::mat4 &AnimationNode::getNodeMatrix() const noexcept
	{
		return __nodeMat;
	}
}
