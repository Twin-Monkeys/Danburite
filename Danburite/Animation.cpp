#include "Animation.h"

using namespace ObjectGL;
using namespace std;

namespace Danburite
{
	Animation::Animation(const size_t id, const float playTime, const string &name) noexcept :
		Object(id), __playTime(playTime), __name(name)
	{}

	AnimationNode &Animation::createNode(const string &nodeName) noexcept
	{
		return __nodeMap.emplace(nodeName, __timestamp).first->second;
	}

	AnimationNode *Animation::getNode(const string &nodeName) noexcept
	{
		auto resultIt = __nodeMap.find(nodeName);
		if (resultIt == __nodeMap.end())
			return nullptr;

		return &resultIt->second;
	}

	const AnimationNode *Animation::getNode(const string &nodeName) const noexcept
	{
		auto resultIt = __nodeMap.find(nodeName);
		if (resultIt == __nodeMap.end())
			return nullptr;

		return &resultIt->second;
	}

	Animation &Animation::setTimestamp(const float timestamp) noexcept
	{
		__timestamp = fmod(timestamp, __playTime);
		return *this;
	}

	Animation &Animation::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + deltaTime);
	}
}