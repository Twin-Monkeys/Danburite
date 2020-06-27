#include "SceneObject.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObject::SceneObject(
		unique_ptr<Mesh> &&pMesh,
		const shared_ptr<AnimationManager>& pAnimationManager,
		const string_view& unitName) noexcept :
		__pAnimManager(pAnimationManager), __name(unitName)
	{
		const shared_ptr<VertexBuffer>& pModelMatrixBuffer =
			reinterpret_pointer_cast<VertexBuffer>(__pModelMatrixBuffer);

		if (!pMesh)
			return;

		pMesh->addVertexBuffer(pModelMatrixBuffer);
		__meshes.emplace(move(pMesh));
	}

	SceneObject::SceneObject(
		unordered_set<unique_ptr<Mesh>> &&meshes,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string_view &unitName) noexcept :
		__pAnimManager(pAnimationManager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<VertexBuffer>(__pModelMatrixBuffer);
		
		for (const unique_ptr<Mesh> &pMesh : meshes)
			pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.swap(meshes);
	}

	void SceneObject::__updateHierarchical_withAnim(const vector<mat4> &parentModelMatrices) noexcept
	{
		Animation *const pAnim = __pAnimManager->getActiveAnimation();

		JointBase *const pJoint = pAnim->getJoint(__name);
		if (pJoint)
		{
			pJoint->updateMatrix();
			__pModelMatrixBuffer->updateMatrices(pJoint->getMatrix());
		}
		else
			__pModelMatrixBuffer->updateMatrices();

		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateHierarchical_withAnim(modelMatrices);
	}

	void SceneObject::__updateHierarchical_withoutAnim(const vector<mat4> &parentModelMatrices) noexcept
	{
		__pModelMatrixBuffer->updateMatrices(parentModelMatrices);
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateHierarchical_withoutAnim(modelMatrices);
	}

	void SceneObject::__updateBoneMatricesHierarchical() noexcept
	{
		Animation *const pAnim = __pAnimManager->getActiveAnimation();
		JointBase *const pJoint = pAnim->getJoint(__name);

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(pJoint->getMatrix());

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateBoneMatricesHierarchical();
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
		if (!__pAnimManager)
		{
			__pModelMatrixBuffer->updateMatrices();
			const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

			for (const shared_ptr<SceneObject> &child : __children)
				child->__updateHierarchical_withoutAnim(modelMatrices);

			return;
		}

		Animation *const pAnim = __pAnimManager->getActiveAnimation();
		if (!pAnim)
		{
			__pModelMatrixBuffer->updateMatrices();
			const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

			for (const shared_ptr<SceneObject> &child : __children)
				child->__updateHierarchical_withoutAnim(modelMatrices);

			return;
		}

		pAnim->adjustTimestamp(deltaTime);

		JointBase *const pJoint = pAnim->getJoint(__name);
		if (pJoint)
		{
			pJoint->updateMatrix();
			__pModelMatrixBuffer->updateMatrices(pJoint->getMatrix());
		}
		else
			__pModelMatrixBuffer->updateMatrices();

		const vector<mat4>& modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		for (const shared_ptr<SceneObject> &child : __children)
			child->__updateHierarchical_withAnim(modelMatrices);

		__updateBoneMatricesHierarchical();
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