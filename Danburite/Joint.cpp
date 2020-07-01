#include "Joint.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Joint::Joint(AnimationManager &animationManager, const string_view &nodeName) noexcept :
		__animMgr(animationManager), __nodeName(nodeName),
		__jointSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::JOINT))
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

		Animation &anim = __animMgr.getActiveAnimation();
		SceneNodeConnecterBase *const pConnecter = anim.getSceneNodeConnecter(__nodeName);
			
		if (pConnecter)
		{
			pConnecter->updateMatrix();
			__jointMat *= pConnecter->getMatrix();
		}

		for (JointUpdateObserver *const pObserver : __observerSet)
			pObserver->onUpdateJointMatrix(__nodeName, __jointMat);

		return *this;
	}

	void Joint::selfDeploy() const noexcept
	{
		__jointSetter.setUniformMat4(ShaderIdentifier::Name::Joint::JOINT_MATRIX, __jointMat);
	}
}