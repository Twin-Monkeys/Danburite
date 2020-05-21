#include "BoneOffsetManager.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "Constant.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	BoneOffsetManager::BoneOffsetManager() :
		__boneSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::BONE))
	{}

	BoneOffset &BoneOffsetManager::createBoneOffset(const string &name, const mat4 &offsetMatrix, const mat4 &hierarchyMatrix)
	{
		const GLuint boneID = GLuint(__boneMatrices.size());
		__boneMatrices.emplace_back(mat4 { 1.f });

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		return *__boneOffsets.emplace_back(make_unique<BoneOffset>(boneID, name, offsetMatrix, hierarchyMatrix));
	}

	BoneOffset &BoneOffsetManager::getBoneOffset(const GLuint id) noexcept
	{
		return *__boneOffsets[id];
	}

	const BoneOffset &BoneOffsetManager::getBoneOffset(const GLuint id) const noexcept
	{
		return *__boneOffsets[id];
	}

	GLuint BoneOffsetManager::getNumBoneOffsets() const noexcept
	{
		return GLuint(__boneOffsets.size());
	}

	void BoneOffsetManager::updateBones(const Animation &animation) noexcept
	{
		for (const unique_ptr<BoneOffset> &pBoneOffset : __boneOffsets)
		{
			const string &boneName = pBoneOffset->getName();
			const Bone *const pBone = animation.getBone(boneName);

			const mat4 *pBoneMat;
			if (pBone)
				pBoneMat = &(pBone->getBoneMatrix());
			else
				pBoneMat = &(Constant::Common::IDENTITY_MATRIX);

			pBoneOffset->calcAnimMatrix(*pBoneMat, __boneMatrices[pBoneOffset->ID]);
		}
	}

	void BoneOffsetManager::selfDeploy() const noexcept
	{
		if (__boneMatrices.empty())
			return;

		__boneSetter.memoryCopy(__boneMatrices.data(), __boneMatrices.size() * sizeof(mat4));
	}
}