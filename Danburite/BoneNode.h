#pragma once

#include "TransformTimeline.h"
#include "Transform.h"
#include <unordered_set>
#include "Constant.h"

namespace Danburite
{
	class BoneNode
	{
	private:
		const std::string __name;

		TransformTimeline __timeline;
		const float &__timestamp;

		Transform __boneTransform;
		glm::mat4 __boneMat { 1.f };

		void __updateTransform() noexcept;

	public:
		BoneNode(const std::string &name, const float &timestampReference) noexcept;

		constexpr const std::string &getName() const noexcept;

		constexpr TransformTimeline &getTimeline() noexcept;
		constexpr const TransformTimeline &getTimeline() const noexcept;

		BoneNode &updateMatrix() noexcept;
		BoneNode &updateMatrix(const glm::mat4 &parentNodeMatrix) noexcept;

		// node matrix
		constexpr const glm::mat4 &getMatrix() const noexcept;
	};

	constexpr const std::string &BoneNode::getName() const noexcept
	{
		return __name;
	}

	constexpr TransformTimeline &BoneNode::getTimeline() noexcept
	{
		return __timeline;
	}

	constexpr const TransformTimeline &BoneNode::getTimeline() const noexcept
	{
		return __timeline;
	}

	constexpr const glm::mat4 &BoneNode::getMatrix() const noexcept
	{
		return __boneMat;
	}
}
