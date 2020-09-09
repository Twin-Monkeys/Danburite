#include "Joint.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Joint::Joint(AnimationManager &animationManager, const string_view &nodeName) noexcept :
		__animMgr(animationManager), __nodeName(nodeName)
	{}

	Joint &Joint::updateMatrix(const mat4 &parentJointMatrix) noexcept
	{
		__transform.updateMatrix();
		__jointMat = (parentJointMatrix * __transform.getMatrix());

		SceneNodeConnecterManager &connecterManager = __animMgr.getActiveAnimation().getConnecterManager();
		SceneNodeConnecterBase *const pConnecter = connecterManager.getSceneNodeConnecter(__nodeName);
			
		if (pConnecter)
		{
			pConnecter->updateMatrix();
			__jointMat *= pConnecter->getMatrix();
		}

		return *this;
	}

	void Joint::selfDeploy() const noexcept
	{
		__jointUB.getInterface().jointMat = __jointMat;

		// todo: 모든 joint가 한번에 deploy 될 수 있도록 array화
		__jointUB.selfDeploy();
	}
}