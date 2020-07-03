#include "Animation.h"

using namespace ObjectGL;
using namespace std;
using namespace glm;

namespace Danburite
{
	Animation::Animation(const size_t id, const float playTime, const string &name) noexcept :
		Object(id), __playTime(playTime), __name(name)
	{}

	AnimatingSceneNodeConnecter &Animation::createAnimatingSceneNodeConnecter(const string &nodeName) noexcept
	{
		unique_ptr<SceneNodeConnecterBase> &pRetVal = __connecterMap[nodeName];
		pRetVal = make_unique<AnimatingSceneNodeConnecter>(nodeName, __timestamp);

		return static_cast<AnimatingSceneNodeConnecter &>(*pRetVal);
	}

	StaticSceneNodeConnecter &Animation::
		createStaticSceneNodeConnecter(const string &nodeName, const mat4 &localConnectingMat) noexcept
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
		if (!__repCnt)
			return *this;

		__timestamp = timestamp;
		
		if ((__timestamp > __playTime) || (__timestamp < 0.f))
		{
			if (__repCnt > 0)
				__repCnt--;

			if (__repCnt)
				__timestamp -= (__playTime * floorf(__timestamp / __playTime));
		}

		return *this;
	}

	Animation& Animation::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + (deltaTime * __playSpeed * float(__playingOrderType)));
	}
}