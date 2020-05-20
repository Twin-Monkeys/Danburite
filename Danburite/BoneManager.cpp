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

	Bone &BoneManager::createBone(const mat4 &offsetMatrix)
	{
		const GLuint boneID = GLuint(__boneMatrices.size());
		__boneMatrices.emplace_back(mat4 { 1.f });

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		return *__bones.emplace_back(make_unique<Bone>(boneID, offsetMatrix, __boneMatrices));
	}

	Bone &BoneManager::getBone(const GLuint id) noexcept
	{
		return *__bones[id];
	}

	const Bone &BoneManager::getBone(const GLuint id) const noexcept
	{
		return *__bones[id];
	}

	GLuint BoneManager::getNumBones() const noexcept
	{
		return GLuint(__bones.size());
	}

	void BoneManager::updateMatrics(const mat4 &nodeMatrix) noexcept
	{
		for (const unique_ptr<Bone> &pBone : __bones)
			pBone->updateMatrix(nodeMatrix);
	}

	void BoneManager::selfDeploy() const noexcept
	{
		if (__boneMatrices.empty())
			return;

		__boneSetter.memoryCopy(__boneMatrices.data(), __boneMatrices.size() * sizeof(mat4));
	}
}