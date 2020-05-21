#include "Animation.h"

using namespace ObjectGL;
using namespace std;

namespace Danburite
{
	Animation::Animation(const size_t id, const float playTime, const string &name) noexcept :
		Object(id), __playTime(playTime), __name(name)
	{}

	Bone &Animation::createBone(const string &name) noexcept
	{
		return __boneMap.emplace(name, Bone { name, __timestamp }).first->second;
	}

	Bone *Animation::getBone(const string &name) noexcept
	{
		auto resultIt = __boneMap.find(name);
		if (resultIt == __boneMap.end())
			return nullptr;

		return &resultIt->second;
	}

	const Bone *Animation::getBone(const string &name) const noexcept
	{
		auto resultIt = __boneMap.find(name);
		if (resultIt == __boneMap.end())
			return nullptr;

		return &resultIt->second;
	}

	Animation& Animation::setTimestamp(const float timestamp) noexcept
	{
		__timestamp = fmod(timestamp, __playTime);
		return *this;
	}

	Animation& Animation::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + deltaTime);
	}

	void Animation::updateBones() noexcept
	{
		if (__pRootBone)
			__pRootBone->updateMatrix();
	}
}