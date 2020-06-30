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

	AnimatingSceneNodeConnecter &Animation::createAnimatingSceneNodeConnecter(const string &nodeName) noexcept
	{
		unique_ptr<SceneNodeConnecterBase> &pRetVal = __connecterMap[nodeName];
		pRetVal = make_unique<AnimatingSceneNodeConnecter>(nodeName, __timestamp);

		return static_cast<AnimatingSceneNodeConnecter &>(*pRetVal);
	}

	StaticSceneNodeConnecter &Animation::createStaticSceneNodeConnecter(const string &nodeName, const mat4 &localConnectingMat) noexcept
	{
		unique_ptr<SceneNodeConnecterBase> &pRetVal = __connecterMap[nodeName];
		pRetVal = make_unique<StaticSceneNodeConnecter>(nodeName, localConnectingMat);

		return static_cast<StaticSceneNodeConnecter &>(*pRetVal);
	}

	SceneNodeConnecterBase* Animation::getSceneNodeConnecter(const string &nodeName) noexcept
	{
		auto resultIt = __connecterMap.find(nodeName);
		if (resultIt == __connecterMap.end())
			return nullptr;

		return resultIt->second.get();
	}

	const SceneNodeConnecterBase *Animation::getSceneNodeConnecter(const string &nodeName) const noexcept
	{
		auto resultIt = __connecterMap.find(nodeName);
		if (resultIt == __connecterMap.end())
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