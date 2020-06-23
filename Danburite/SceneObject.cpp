#include "SceneObject.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObject::SceneObject(
		unique_ptr<Mesh> pMesh,
		const mat4 &nodeTransformationMat,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string_view &unitName) noexcept :
		__pModelMatrixBuffer(make_shared<ModelMatrixBuffer>(nodeTransformationMat)),
		__pAnimManager(pAnimationManager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<VertexBuffer>(__pModelMatrixBuffer);

		pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.emplace(move(pMesh));
	}

	SceneObject::SceneObject(
		unordered_set<unique_ptr<Mesh>> &&meshes,
		const mat4 &nodeTransformationMat,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string_view &unitName) noexcept :
		__pModelMatrixBuffer(make_shared<ModelMatrixBuffer>(nodeTransformationMat)),
		__pAnimManager(pAnimationManager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<VertexBuffer>(__pModelMatrixBuffer);
		
		for (const unique_ptr<Mesh> &pMesh : meshes)
			pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.swap(meshes);
	}

	void SceneObject::__updateBoneHierarchical(const mat4 &parentNodeMatrix) noexcept
	{
		Animation &anim = *(__pAnimManager->getActiveAnimation());

		BoneNode* pBoneNode = anim.getBoneNode(__name);
		if (!pBoneNode)
			pBoneNode = &anim.createBoneNode(__name);

		pBoneNode->updateMatrix(parentNodeMatrix);

		const mat4 &boneNodeMatrix = pBoneNode->getMatrix();

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateBoneHierarchical(boneNodeMatrix);
	}

	void SceneObject::__updateHierarchical_withAnim(const vector<mat4> &parentModelMatrices)
	{
		Animation &anim = *(__pAnimManager->getActiveAnimation());

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(anim);

		__pModelMatrixBuffer->updateMatrix(parentModelMatrices);
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateHierarchical_withAnim(modelMatrices);
	}

	void SceneObject::__updateHierarchical_withoutAnim(const vector<mat4> &parentModelMatrices)
	{
		__pModelMatrixBuffer->updateMatrix(parentModelMatrices);
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateHierarchical_withoutAnim(modelMatrices);
	}

	Transform &SceneObject::getTransform(const size_t idx) const noexcept
	{
		return __pModelMatrixBuffer->getTransform(idx);
	}

	void SceneObject::setNumInstances(const GLsizei numInstances) noexcept
	{
		__pModelMatrixBuffer->setNumInstances(numInstances);

		for (const shared_ptr<SceneObject> &child : __children)
			child->setNumInstances(numInstances);
	}

	AnimationManager &SceneObject::getAnimationManager() noexcept
	{
		return *__pAnimManager;
	}

	const AnimationManager &SceneObject::getAnimationManager() const noexcept
	{
		return *__pAnimManager;
	}

	void SceneObject::update(const float deltaTime) noexcept
	{
		__pModelMatrixBuffer->updateMatrix();
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		if (!__pAnimManager)
		{
			for (const shared_ptr<SceneObject> &child : __children)
				child->__updateHierarchical_withoutAnim(modelMatrices);

			return;
		}

		Animation *const pAnim = __pAnimManager->getActiveAnimation();
		if (!pAnim)
		{
			for (const shared_ptr<SceneObject> &child : __children)
				child->__updateHierarchical_withoutAnim(modelMatrices);

			return;
		}

		pAnim->adjustTimestamp(deltaTime);

		BoneNode *const pBoneNode = pAnim->getBoneNode(__name);
		if (pBoneNode)
			pBoneNode->updateMatrix();

		const mat4 *pNodeMatrix;
		if (pBoneNode)
			pNodeMatrix = &(pBoneNode->getMatrix());
		else
			pNodeMatrix = &Constant::Common::IDENTITY_MATRIX;

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateBoneHierarchical(*pNodeMatrix);

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(*pAnim);

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateHierarchical_withAnim(modelMatrices);
	}

	void SceneObject::draw() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->draw(GLsizei(NUM_INSTANCES));

		for (const shared_ptr<SceneObject> &child : __children)
			child->draw();
	}

	void SceneObject::rawDrawcall() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->rawDrawcall(GLsizei(NUM_INSTANCES));

		for (const shared_ptr<SceneObject> &child : __children)
			child->rawDrawcall();
	}
}