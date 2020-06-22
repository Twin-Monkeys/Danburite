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

	Bone &BoneOffsetManager::createBoneOffset(const string &name, const mat4 &offsetMatrix, const mat4 &hierarchyMatrix)
	{
		const GLuint boneID = GLuint(__boneMatrices.size());
		__boneMatrices.emplace_back(mat4 { 1.f });

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		return *__boneOffsets.emplace_back(make_unique<Bone>(boneID, name, offsetMatrix, hierarchyMatrix));
	}

	Bone &BoneOffsetManager::getBoneOffset(const GLuint id) noexcept
	{
		return *__boneOffsets[id];
	}

	const Bone &BoneOffsetManager::getBoneOffset(const GLuint id) const noexcept
	{
		return *__boneOffsets[id];
	}

	GLuint BoneOffsetManager::getNumBoneOffsets() const noexcept
	{
		return GLuint(__boneOffsets.size());
	}

	void BoneOffsetManager::updateMatrices(const Animation &animation) noexcept
	{
		for (const unique_ptr<Bone> &pBoneOffset : __boneOffsets)
		{
			const string &boneName = pBoneOffset->getNodeName();
			const BoneNode *const pBoneNode = animation.getBoneNode(boneName);

			const mat4 *pBoneNodeMat;
			if (pBoneNode)
				pBoneNodeMat = &(pBoneNode->getMatrix());
			else
				pBoneNodeMat = &(Constant::Common::IDENTITY_MATRIX);

			pBoneOffset->calcBoneMatrix(*pBoneNodeMat, __boneMatrices[pBoneOffset->ID]);
		}
	}

	void BoneOffsetManager::selfDeploy() const noexcept
	{
		if (__boneMatrices.empty())
			return;

		__boneSetter.memoryCopy(__boneMatrices.data(), __boneMatrices.size() * sizeof(mat4));
	}
}