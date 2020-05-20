#pragma once

#include "Timeline.h"
#include <glm/glm.hpp>
#include "Quaternion.h"

namespace Danburite
{
	class TransformTimeline
	{
	public:
		Timeline<glm::vec3> posTimeline;
		Timeline<Quaternion> rotationTimeline;
		Timeline<glm::vec3> scaleTimeline { { 1.f, 1.f, 1.f } };

		constexpr TransformTimeline &setPreStateWrappingType(const TimelineWrappingType type) noexcept;
		constexpr TransformTimeline &setPostStateWrappingType(const TimelineWrappingType type) noexcept;
		std::tuple<glm::vec3, Quaternion, glm::vec3> sample(const float timestamp) const noexcept;
	};

	constexpr TransformTimeline &TransformTimeline::setPreStateWrappingType(const TimelineWrappingType type) noexcept
	{
		posTimeline.setPreStateWrappingType(type);
		rotationTimeline.setPreStateWrappingType(type);
		scaleTimeline.setPreStateWrappingType(type);

		return *this;
	}

	constexpr TransformTimeline& TransformTimeline::setPostStateWrappingType(const TimelineWrappingType type) noexcept
	{
		posTimeline.setPostStateWrappingType(type);
		rotationTimeline.setPostStateWrappingType(type);
		scaleTimeline.setPostStateWrappingType(type);

		return *this;
	}
}
