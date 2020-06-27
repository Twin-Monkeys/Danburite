#include "Animation.h"

using namespace ObjectGL;
using namespace std;
using namespace glm;

namespace Danburite
{
	Animation::Animation(
		const size_t id, const float playTime,
		const weak_ptr<JointUpdateObserver> &pDefaultJointUpdateObserver, const string &name) noexcept :
		Object(id), __playTime(playTime),
		__pDefaultJointUpdateObserver(pDefaultJointUpdateObserver), __name(name)
	{}

	AnimatingJoint &Animation::createAnimatingJoint(const string &name) noexcept
	{
		unique_ptr<JointBase> &pRetVal = __jointMap[name];
		pRetVal = make_unique<AnimatingJoint>(name, __timestamp);
		pRetVal->getObserverSet().add(__pDefaultJointUpdateObserver);

		return static_cast<AnimatingJoint &>(*pRetVal);
	}

	StaticJoint &Animation::createStaticJoint(const string &name, const mat4 &localJointMatrix) noexcept
	{
		unique_ptr<JointBase> &pRetVal = __jointMap[name];
		pRetVal = make_unique<StaticJoint>(name, localJointMatrix);
		pRetVal->getObserverSet().add(__pDefaultJointUpdateObserver);

		return static_cast<StaticJoint &>(*pRetVal);
	}

	JointBase* Animation::getJoint(const string &name) noexcept
	{
		auto resultIt = __jointMap.find(name);
		if (resultIt == __jointMap.end())
			return nullptr;

		return resultIt->second.get();
	}

	const JointBase *Animation::getJoint(const string &name) const noexcept
	{
		auto resultIt = __jointMap.find(name);
		if (resultIt == __jointMap.end())
			return nullptr;

		return resultIt->second.get();
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