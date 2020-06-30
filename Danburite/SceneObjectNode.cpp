#include "SceneObjectNode.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObjectNode::SceneObjectNode(
		unordered_set<unique_ptr<Mesh>> &&meshes, Joint *const pJoint, const string_view &name) noexcept :
		__pJoint(pJoint), __name(name)
	{
		__meshes.swap(meshes);
	}

	void SceneObjectNode::__updateHierarchical_withAnim(const vector<mat4> &parentModelMatrices) noexcept
	{
		Animation *const pAnim = __pAnimManager->getActiveAnimation();

		SceneNodeConnecterBase *const pJoint = pAnim->getSceneNodeConnecter(__name);
		if (pJoint)
		{
			pJoint->updateMatrix();
			__pModelMatrixBuffer->updateMatrices(parentModelMatrices, pJoint->getMatrix());
		}
		else
			__pModelMatrixBuffer->updateMatrices(parentModelMatrices);

		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();
		__pAnimManager->onUpdateJointMatrix(__name, modelMatrices[0]);

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->__updateHierarchical_withAnim(modelMatrices);
	}

	void SceneObjectNode::__updateHierarchical_withoutAnim(const vector<mat4> &parentModelMatrices) noexcept
	{
		__pModelMatrixBuffer->updateMatrices(parentModelMatrices);
		const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->__updateHierarchical_withoutAnim(modelMatrices);
	}

	void SceneObjectNode::__updateBoneMatricesHierarchical() noexcept
	{
		Animation *const pAnim = __pAnimManager->getActiveAnimation();
		SceneNodeConnecterBase *const pJoint = pAnim->getSceneNodeConnecter(__name);

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(__pModelMatrixBuffer->getModelMatrices()[0]);

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->__updateBoneMatricesHierarchical();
	}

	void SceneObjectNode::addChild(SceneObjectNode *const pChild) noexcept
	{
		__children.emplace(pChild);
	}

	void SceneObjectNode::update(const float deltaTime) noexcept
	{
		if (!__pAnimManager)
		{
			__pModelMatrixBuffer->updateMatrices();
			const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

			for (const shared_ptr<SceneObjectNode> &child : __children)
				child->__updateHierarchical_withoutAnim(modelMatrices);

			return;
		}

		Animation *const pAnim = __pAnimManager->getActiveAnimation();
		if (!pAnim)
		{
			__pModelMatrixBuffer->updateMatrices();
			const vector<mat4> &modelMatrices = __pModelMatrixBuffer->getModelMatrices();

			for (const shared_ptr<SceneObjectNode> &child : __children)
				child->__updateHierarchical_withoutAnim(modelMatrices);

			return;
		}

		pAnim->adjustTimestamp(deltaTime);

		SceneNodeConnecterBase *const pJoint = pAnim->getSceneNodeConnecter(__name);
		if (pJoint)
		{
			pJoint->updateMatrix();
			__pModelMatrixBuffer->updateMatrices(pJoint->getMatrix());
		}
		else
			__pModelMatrixBuffer->updateMatrices();

		const vector<mat4>& modelMatrices = __pModelMatrixBuffer->getModelMatrices();
		__pAnimManager->onUpdateJointMatrix(__name, modelMatrices[0]);

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->__updateHierarchical_withAnim(modelMatrices);

		__updateBoneMatricesHierarchical();
	}

	void SceneObjectNode::draw() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->draw(GLsizei(NUM_INSTANCES));

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->draw();
	}

	void SceneObjectNode::rawDrawcall() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->rawDrawcall(GLsizei(NUM_INSTANCES));

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->rawDrawcall();
	}
}