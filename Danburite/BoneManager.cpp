#include "BoneManager.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "Constant.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	BoneManager::BoneManager() :
		__boneSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::BONE))
	{}

	Bone &BoneManager::createBone(const string &jointName, const mat4 &offsetMatrix)
	{
		const GLuint boneID = GLuint(__boneMatrices.size());
		__boneMatrices.emplace_back();

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		const unique_ptr<Bone> &pBone = __bones.emplace_back(make_unique<Bone>(boneID, offsetMatrix));
		__targetJointToBonesMap[jointName].emplace_back(pBone.get());

		return *pBone;
	}

	Bone *BoneManager::getBone(const GLuint id) noexcept
	{
		if (__bones.size() <= size_t(id))
			return nullptr;

		return __bones[id].get();
	}

	const Bone *BoneManager::getBone(const GLuint id) const noexcept
	{
		if (__bones.size() <= size_t(id))
			return nullptr;

		return __bones[id].get();
	}

	GLuint BoneManager::getNumBones() const noexcept
	{
		return GLuint(__bones.size());
	}

	void BoneManager::updateTargetJointMatrices(const string &jointName, const mat4 &jointMatrix) noexcept
	{
		for (Bone *const pBone : __targetJointToBonesMap[jointName])
			pBone->setTargetJointMatrix(jointMatrix);
	}

	void BoneManager::updateSourceJointMatrices(const mat4 &jointMatrix) noexcept
	{
		for (const unique_ptr<Bone>& pBone : __bones)
			pBone->setSourceJointMatrix(jointMatrix);
	}

	void BoneManager::updateBoneMatrices() noexcept
	{
		for (size_t i = 0ULL; i < __bones.size(); i++)
		{
			Bone &bone = *__bones[i];
			
			bone.updateBoneMatrices();
			__boneMatrices[i] = bone.getBoneMatrix();
		}
	}

	void BoneManager::selfDeploy() const noexcept
	{
		if (__boneMatrices.empty())
			return;

		__boneSetter.memoryCopy(__boneMatrices.data(), __boneMatrices.size() * sizeof(mat4));
	}
}