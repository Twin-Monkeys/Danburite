#include "RenderUnit.h"
#include "RenderUnitManager.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	RenderUnit::RenderUnit(
		unique_ptr<Mesh> pMesh,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string_view &unitName) noexcept :
		__pAnimManager(pAnimationManager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);

		pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.emplace(move(pMesh));
	}

	RenderUnit::RenderUnit(
		unordered_set<unique_ptr<Mesh>> &&meshes,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string_view &unitName) noexcept :
		__pAnimManager(pAnimationManager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);
		
		for (const unique_ptr<Mesh> &pMesh : meshes)
			pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.swap(meshes);
	}

	void RenderUnit::__updateBoneHierarchical(const mat4 &parentNodeMatrix) noexcept
	{
		Animation &anim = *(__pAnimManager->getActiveAnimation());

		Bone* const pBone = anim.getBone(__name);
		if (pBone)
			pBone->updateMatrix(parentNodeMatrix);

		const mat4 *pNodeMatrix;
		if (pBone)
			pNodeMatrix = &(pBone->getBoneMatrix());
		else
			pNodeMatrix = &parentNodeMatrix;

		__children.safeTraverse(&RenderUnit::__updateBoneHierarchical, *pNodeMatrix);
	}

	void RenderUnit::__updateHierarchical_withAnim(const vector<mat4> &parentModelMatrices)
	{
		Animation &anim = *(__pAnimManager->getActiveAnimation());

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(anim);

		__pModelMatrixBuffer->updateMatrix(parentModelMatrices);
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		__children.safeTraverse(&RenderUnit::__updateHierarchical_withAnim, modelMatrices);
	}

	void RenderUnit::__updateHierarchical_withoutAnim(const vector<mat4> &parentModelMatrices)
	{
		__pModelMatrixBuffer->updateMatrix(parentModelMatrices);
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		__children.safeTraverse(&RenderUnit::__updateHierarchical_withoutAnim, modelMatrices);
	}

	Transform &RenderUnit::getTransform(const size_t idx) const noexcept
	{
		return __pModelMatrixBuffer->getTransform(idx);
	}

	void RenderUnit::setNumInstances(const GLsizei numInstances) noexcept
	{
		__pModelMatrixBuffer->setNumInstances(numInstances);
		__children.safeTraverse(&RenderUnit::setNumInstances, numInstances);
	}

	void RenderUnit::update(const float deltaTime) noexcept
	{
		__pModelMatrixBuffer->updateMatrix();
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		if (!__pAnimManager)
		{
			__children.safeTraverse(&RenderUnit::__updateHierarchical_withoutAnim, modelMatrices);
			return;
		}

		Animation *const pAnim = __pAnimManager->getActiveAnimation();
		if (!pAnim)
		{
			__children.safeTraverse(&RenderUnit::__updateHierarchical_withoutAnim, modelMatrices);
			return;
		}

		pAnim->adjustTimestamp(deltaTime);

		Bone* const pBone = pAnim->getBone(__name);
		if (pBone)
			pBone->updateMatrix();

		const mat4* pNodeMatrix;
		if (pBone)
			pNodeMatrix = &(pBone->getBoneMatrix());
		else
			pNodeMatrix = &Constant::Common::IDENTITY_MATRIX;

		__children.safeTraverse(&RenderUnit::__updateBoneHierarchical, *pNodeMatrix);

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(*pAnim);

		__children.safeTraverse(&RenderUnit::__updateHierarchical_withAnim, modelMatrices);
	}

	void RenderUnit::draw() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->draw(GLsizei(NUM_INSTANCES));

		__children.safeTraverse(&RenderUnit::draw);
	}

	void RenderUnit::rawDrawcall() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->rawDrawcall(GLsizei(NUM_INSTANCES));

		__children.safeTraverse(&RenderUnit::rawDrawcall);
	}
}