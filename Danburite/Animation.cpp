#include "Animation.h"

using namespace ObjectGL;
using namespace std;

namespace Danburite
{
	Animation::Animation(const size_t id, const float playTime, const string &name) noexcept :
		Object(id), __playTime(playTime), __name(name)
	{}

	BoneNode &Animation::createBoneNode(const string &name) noexcept
	{
		return __boneNodeMap.emplace(name, BoneNode { name, __timestamp }).first->second;
	}

	BoneNode *Animation::getBoneNode(const string &name) noexcept
	{
		auto resultIt = __boneNodeMap.find(name);
		if (resultIt == __boneNodeMap.end())
			return nullptr;

		return &resultIt->second;
	}

	const BoneNode *Animation::getBoneNode(const string &name) const noexcept
	{
		auto resultIt = __boneNodeMap.find(name);
		if (resultIt == __boneNodeMap.end())
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
		return setTimestamp(__timestamp + (deltaTime * __playSpeed));
	}
}