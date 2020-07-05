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
		__jointSetter.setUniformMat4(ShaderIdentifier::Name::Joint::JOINT_MATRIX, __jointMat);
	}
}