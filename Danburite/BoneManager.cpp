#include "BoneManager.h"
#include "Constant.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	BoneManager::BoneManager(const JointManager &jointManager) :
		__jointMgr(jointManager)
	{}

	Bone &BoneManager::createBone(const string &targetNodeName, const string &srcNodeName, const mat4 &offsetMatrix)
	{
		const GLuint boneID = GLuint(__bones.size());

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		return *__bones.emplace_back(
			make_unique<Bone>(boneID, __jointMgr, targetNodeName, srcNodeName, offsetMatrix));
	}

	void BoneManager::updateBones() noexcept
	{
		BoneUniformInterface &boneUniformInterface = __boneUB.getInterface();

		for (size_t i = 0ULL; i < __bones.size(); i++)
		{
			Bone &bone = *__bones[i];
			bone.updateMatrix();
			boneUniformInterface.boneMatrices.set(i, bone.getMatrix());
		}
	}

	void BoneManager::selfDeploy() const noexcept
	{
		__boneUB.selfDeploy();
	}
}