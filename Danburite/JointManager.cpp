#include "JointManager.h"

using namespace std;

namespace Danburite
{
	JointManager::JointManager(AnimationManager &animationManager) noexcept :
		__animMgr(animationManager)
	{}

	Joint &JointManager::createJoint(const string &nodeName) noexcept
	{
		Joint* const pJoint =
			__joints.emplace_back(make_unique<Joint>(__animMgr, nodeName)).get();

		__nameToJointMap.emplace(nodeName, pJoint);

		return *pJoint;
	}

	Joint *JointManager::getJoint(const string &nodeName) noexcept
	{
		auto resultIt = __nameToJointMap.find(nodeName);
		if (resultIt == __nameToJointMap.end())
			return nullptr;

		return resultIt->second;
	}

	const Joint *JointManager::getJoint(const string &nodeName) const noexcept
	{
		auto resultIt = __nameToJointMap.find(nodeName);
		if (resultIt == __nameToJointMap.end())
			return nullptr;

		return resultIt->second;
	}
}