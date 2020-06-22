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

	Bone &BoneManager::createBone(const string &boneNodeName, const mat4 &offsetMatrix, const mat4 &hierarchyMatrix)
	{
		const GLuint boneID = GLuint(__boneMatrices.size());
		__boneMatrices.emplace_back(mat4 { 1.f });

		if (boneID >= Constant::Animation::MAX_NUM_BONES)
			throw BoneException("the number of bones cannot be greater than MAX_NUM_BONES.");

		return *__bones.emplace_back(make_unique<Bone>(boneID, boneNodeName, offsetMatrix, hierarchyMatrix));
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

	void BoneManager::updateMatrices(const Animation &animation) noexcept
	{
		for (const unique_ptr<Bone> &pBone : __bones)
		{
			const string &nodeName = pBone->getNodeName();
			const BoneNode *const pBoneNode = animation.getBoneNode(nodeName);

			const mat4 *pBoneNodeMat;
			if (pBoneNode)
				pBoneNodeMat = &(pBoneNode->getMatrix());
			else
				pBoneNodeMat = &(Constant::Common::IDENTITY_MATRIX);

			pBone->calcBoneMatrix(*pBoneNodeMat, __boneMatrices[pBone->ID]);
		}
	}

	void BoneManager::selfDeploy() const noexcept
	{
		if (__boneMatrices.empty())
			return;

		__boneSetter.memoryCopy(__boneMatrices.data(), __boneMatrices.size() * sizeof(mat4));
	}
}