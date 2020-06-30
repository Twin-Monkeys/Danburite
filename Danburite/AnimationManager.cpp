#include "AnimationManager.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Animation &AnimationManager::createAnimation(const float playTime, const string &name) noexcept
	{
		return *__animations.emplace_back(
			make_unique<Animation>(__animations.size(), playTime, shared_from_this(), name));
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

	bool AnimationManager::activateAnimation(const size_t animationID) noexcept
	{
		if (__animations.size() <= animationID)
			return false;

		__activeAnimID = animationID;
		return true;
	}

	Animation *AnimationManager::getActiveAnimation() noexcept
	{
		if (__animations.empty())
			return nullptr;

		return &getAnimation(__activeAnimID);
	}

	const Animation *AnimationManager::getActiveAnimation() const noexcept
	{
		if (__animations.empty())
			return nullptr;

		return &getAnimation(__activeAnimID);
	}

	BoneManager &AnimationManager::createBoneManager() noexcept
	{
		return *__boneMgrs.emplace_back(make_unique<BoneManager>());
	}
}