#pragma once

#include "JointBase.h"
#include "TransformTimeline.h"
#include "Transform.h"

namespace Danburite
{
	class AnimatingJoint : public JointBase
	{
	private:
		TransformTimeline __timeline;
		const float &__timestampRef;

	protected:
		virtual void _onUpdateMatrix(glm::mat4 &jointMat) noexcept override;

	public:
		AnimatingJoint(const std::string_view &name, const float &timestampReference) noexcept;

		constexpr TransformTimeline &getTimeline() noexcept;
		constexpr const TransformTimeline &getTimeline() const noexcept;
	};

	constexpr TransformTimeline& AnimatingJoint::getTimeline() noexcept
	{
		return __timeline;
	}

	constexpr const TransformTimeline& AnimatingJoint::getTimeline() const noexcept
	{
		return __timeline;
	}
}
