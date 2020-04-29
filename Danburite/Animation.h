#pragma once

#include "TransformComponent.h"
#include "Updatable.h"
#include <map>

namespace Danburite
{
	class Animation : public Updatable
	{
	private:
		std::map<float, TransformComponent, bool(*)(float, float)> __keyframes;

		float __timestamp = 0.f;
		float __playTime = 0.f;

		TransformComponent __currentComponent;

	public:
		Animation() noexcept;

		constexpr const TransformComponent &getCurrentState() const noexcept;
		void addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept;

		virtual void update(const float deltaTime) noexcept override;
	};

	constexpr const TransformComponent &Animation::getCurrentState() const noexcept
	{
		return __currentComponent;
	}
}
