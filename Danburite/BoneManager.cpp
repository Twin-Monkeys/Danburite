#include "BoneManager.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "Constant.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	BoneManager::BoneManager(const JointManager &jointManager) :
		__jointMgr(jointManager),
		__boneSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::BONE))
	{}

	Bone &BoneManager::createBone(const string &targetNodeName, const string &srcNodeName, const mat4 &offsetMatrix)
	{
		const GLuint boneID = GLuint(__boneMatrices.size());
		__boneMatrices.emplace_back();

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		return *__bones.emplace_back(
			make_unique<Bone>(boneID, __jointMgr, targetNodeName, srcNodeName, offsetMatrix));
	}

	void BoneManager::updateBones() noexcept
	{
		for (size_t i = 0ULL; i < __bones.size(); i++)
			__bones[i]->calcMatrix(__boneMatrices[i]);
	}

	void BoneManager::selfDeploy() const noexcept
	{
		if (__boneMatrices.empty())
			return;

		__boneSetter.memoryCopy(__boneMatrices.data(), __boneMatrices.size() * sizeof(mat4));
	}
}