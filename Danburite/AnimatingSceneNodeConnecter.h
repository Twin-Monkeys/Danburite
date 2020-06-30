#pragma once

#include "SceneNodeConnecterBase.h"
#include "TransformTimeline.h"

namespace Danburite
{
	class AnimatingSceneNodeConnecter : public SceneNodeConnecterBase
	{
	private:
		TransformTimeline __timeline;
		const float &__timestampRef;

	protected:
		virtual void _onUpdateLocalMatrix(glm::mat4 &localConnectingMat) noexcept override;

	public:
		AnimatingSceneNodeConnecter(const std::string_view &name, const float &timestampReference) noexcept;

		constexpr TransformTimeline &getTimeline() noexcept;
		constexpr const TransformTimeline &getTimeline() const noexcept;
	};

	constexpr TransformTimeline& AnimatingSceneNodeConnecter::getTimeline() noexcept
	{
		return __timeline;
	}

	constexpr const TransformTimeline& AnimatingSceneNodeConnecter::getTimeline() const noexcept
	{
		return __timeline;
	}
}
