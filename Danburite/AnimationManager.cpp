#include "AnimationManager.h"

using namespace std;

namespace Danburite
{
	Animation &AnimationManager::createAnimation(const float playTime, const string &name) noexcept
	{
		return *__animations.emplace_back(make_unique<Animation>(__animations.size() + 1ULL, playTime, name));
	}

	Animation &AnimationManager::getAnimation(const size_t id) noexcept
	{
		return *__animations[id];
	}

	const Animation &AnimationManager::getAnimation(const size_t id) const noexcept
	{
		return *__animations[id];
	}

	size_t AnimationManager::getNumAnimations() const noexcept
	{
		return __animations.size();
	}

	Animation &AnimationManager::getActiveAnimation() noexcept
	{
		return getAnimation(__activeAnimID);
	}

	const Animation &AnimationManager::getActiveAnimation() const noexcept
	{
		return getAnimation(__activeAnimID);
	}
}