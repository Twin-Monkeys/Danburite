#include "Animation.h"

using namespace ObjectGL;
using namespace std;

namespace Danburite
{
	Animation::Animation(const size_t id, const float playTime, const string &name) noexcept :
		Object(id), __playTime(playTime), __name(name)
	{}

	AnimationNode &Animation::getNode(const string &nodeName) noexcept
	{
		return __nodeMap.emplace(nodeName, __playTime).first->second;
	}

	const AnimationNode &Animation::getNode(const string &nodeName) const noexcept
	{
		return __nodeMap.at(nodeName);
	}

	bool Animation::isExistentNode(const string &nodeName) const noexcept
	{
		return __nodeMap.count(nodeName);
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