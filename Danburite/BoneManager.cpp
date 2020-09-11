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
		for (size_t i = 0ULL; i < __bones.size(); i++)
			__bones[i]->updateMatrix();
	}

	void BoneManager::selfDeploy() const noexcept
	{
		BoneUniformInterface& boneUniformInterface = __boneUB.getInterface();

		for (size_t i = 0ULL; i < __bones.size(); i++)
			boneUniformInterface.boneMatrices = { i, __bones[i]->getMatrix() };

		__boneUB.selfDeploy();
	}
}