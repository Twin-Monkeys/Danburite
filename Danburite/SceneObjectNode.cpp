#include "SceneObjectNode.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObjectNode::SceneObjectNode(
		const shared_ptr<ModelMatrixBuffer> &pModelMatrixBuffer,
		JointManager &jointManager, const string &name) noexcept :
		__pModelMatrixBuffer(pModelMatrixBuffer), __jointManager(jointManager),
		__joint(jointManager.addJoint(name)), __name(name)
	{}

	BoneManager &SceneObjectNode::addBoneManger() noexcept
	{
		return *__boneMgrs.emplace_back(make_unique<BoneManager>(__jointManager));
	}

	Mesh &SceneObjectNode::addMesh(
		const shared_ptr<VertexArray>& pVertexArray, const shared_ptr<Material>& pMaterial) noexcept
	{
		return addMesh(pVertexArray, pMaterial, addBoneManger());
	}

	Mesh &SceneObjectNode::addMesh(
		const shared_ptr<VertexArray> &pVertexArray, const shared_ptr<Material> &pMaterial,
		const BoneManager &boneManager) noexcept
	{
		return *__meshes.emplace_back(
			make_unique<Mesh>(pVertexArray, pMaterial, __pModelMatrixBuffer, boneManager));
	}

	void SceneObjectNode::addChild(SceneObjectNode &child) noexcept
	{
		__children.emplace(&child);
	}

	void SceneObjectNode::updateJoint(const mat4 &parentJointMatrix) noexcept
	{
		__joint.updateMatrix(parentJointMatrix);
		const mat4 &jointMatrix = __joint.getMatrix();

		for (SceneObjectNode *const pChild : __children)
			pChild->updateJoint(jointMatrix);
	}

	void SceneObjectNode::updateBones() noexcept
	{
		for (const unique_ptr<BoneManager> &pBoneMgr : __boneMgrs)
			pBoneMgr->updateBones();

		for (SceneObjectNode *const pChild : __children)
			pChild->updateBones();
	}

	void SceneObjectNode::draw(const size_t numInstances) noexcept
	{
		__joint.selfDeploy();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->draw(GLsizei(numInstances));

		for (SceneObjectNode *const pChild : __children)
			pChild->draw(numInstances);
	}

	void SceneObjectNode::rawDrawcall(const size_t numInstances) noexcept
	{
		__joint.selfDeploy();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->rawDrawcall(GLsizei(numInstances));

		for (SceneObjectNode *const pChild : __children)
			pChild->rawDrawcall(numInstances);
	}
}