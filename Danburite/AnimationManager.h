#pragma once

#include "Animation.h"
#include <memory>

namespace Danburite
{
	class AnimationManager
	{
	private:
		std::vector<std::unique_ptr<Animation>> __animations;
		size_t __activeAnimID = 0ULL;

	public:
		AnimationManager() noexcept;

		Animation &createAnimation(const float playTime, const std::string &name = "") noexcept;
		Animation &getAnimation(const size_t id = 0U) noexcept;
		const Animation &getAnimation(const size_t id = 0U) const noexcept;

		size_t getNumAnimations() const noexcept;

		bool activateAnimation(const size_t animationID) noexcept;

		Animation &getActiveAnimation() noexcept;
		const Animation &getActiveAnimation() const noexcept;
	};
}
