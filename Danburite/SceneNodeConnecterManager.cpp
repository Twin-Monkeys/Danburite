#include "SceneNodeConnecterManager.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	SceneNodeConnecterManager::SceneNodeConnecterManager(const float &timestampReference) noexcept :
		__timestampRef(timestampReference)
	{}

	AnimatingSceneNodeConnecter& SceneNodeConnecterManager::addAnimatingSceneNodeConnecter(const string& nodeName)
	{
		if (getSceneNodeConnecter(nodeName))
			throw SceneNodeConnecterException("There is a connecter which has same name already.");

		unique_ptr<SceneNodeConnecterBase>& pRetVal = __connecterMap[nodeName];
		pRetVal = make_unique<AnimatingSceneNodeConnecter>(nodeName, __timestampRef);

		return static_cast<AnimatingSceneNodeConnecter&>(*pRetVal);
	}

	StaticSceneNodeConnecter& SceneNodeConnecterManager::addStaticSceneNodeConnecter(
		const string& nodeName, const mat4& localConnectingMat)
	{
		if (getSceneNodeConnecter(nodeName))
			throw SceneNodeConnecterException("There is a connecter which has same name already.");

		unique_ptr<SceneNodeConnecterBase>& pRetVal = __connecterMap[nodeName];
		pRetVal = make_unique<StaticSceneNodeConnecter>(nodeName, localConnectingMat);

		return static_cast<StaticSceneNodeConnecter&>(*pRetVal);
	}

	SceneNodeConnecterBase *SceneNodeConnecterManager::getSceneNodeConnecter(const string& nodeName) noexcept
	{
		auto resultIt = __connecterMap.find(nodeName);
		if (resultIt == __connecterMap.end())
			return nullptr;

		return resultIt->second.get();
	}

	const SceneNodeConnecterBase *SceneNodeConnecterManager::getSceneNodeConnecter(const string& nodeName) const noexcept
	{
		auto resultIt = __connecterMap.find(nodeName);
		if (resultIt == __connecterMap.end())
			return nullptr;

		return resultIt->second.get();
	}
}