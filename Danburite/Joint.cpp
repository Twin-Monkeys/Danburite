#include "Joint.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Joint::Joint(const AnimationManager &animationManager, const string_view &nodeName) noexcept :
		__animMgr(animationManager), __nodeName(nodeName)
	{}

	Joint &Joint::addObserver(JointUpdateObserver *const pObserver) noexcept
	{
		if (pObserver)
			__observerSet.emplace(pObserver);
		else
			assert(false);

		return *this;
	}

	Joint &Joint::updateMatrix(const mat4 &parentJointMatrix) noexcept
	{
		__transform.updateMatrix();
		__jointMat = (parentJointMatrix * __transform.getMatrix());

		const Animation &anim = __animMgr.getActiveAnimation();
		const SceneNodeConnecterBase *const pConnecter = anim.getSceneNodeConnecter(__nodeName);
			
		if (pConnecter)
			__jointMat *= pConnecter->getMatrix();

		for (JointUpdateObserver *const pObserver : __observerSet)
			pObserver->onUpdateJointMatrix(__nodeName, __jointMat);
	}
}