#pragma once

#include "TransformTimeline.h"
#include "Transform.h"
#include <unordered_set>
#include "Constant.h"

namespace Danburite
{
	class Bone
	{
	private:
		const std::string __name;

		TransformTimeline __timeline;
		const float &__timestamp;

		Transform __boneTransform;
		glm::mat4 __boneMat { 1.f };

		void __updateTransform() noexcept;

	public:
		Bone(const std::string &name, const float &timestampReference) noexcept;

		constexpr const std::string &getName() const noexcept;

		constexpr TransformTimeline &getTimeline() noexcept;
		constexpr const TransformTimeline &getTimeline() const noexcept;

		Bone &updateMatrix() noexcept;
		Bone &updateMatrix(const glm::mat4 &parentNodeMatrix) noexcept;

		constexpr const glm::mat4 &getBoneMatrix() const noexcept;
	};

	constexpr const std::string &Bone::getName() const noexcept
	{
		return __name;
	}

	constexpr TransformTimeline &Bone::getTimeline() noexcept
	{
		return __timeline;
	}

	constexpr const TransformTimeline &Bone::getTimeline() const noexcept
	{
		return __timeline;
	}

	constexpr const glm::mat4 &Bone::getBoneMatrix() const noexcept
	{
		return __boneMat;
	}
}
