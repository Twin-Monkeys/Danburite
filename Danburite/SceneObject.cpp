#include "SceneObject.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObjectNode &SceneObject::createNode(
		const shared_ptr<VertexArray> &pVertexArray,
		const shared_ptr<Material> &pMaterial, const bool setAsRoot, const string_view &name) noexcept
	{
		return createNode({ { pVertexArray, pMaterial } }, setAsRoot, name);
	}

	SceneObjectNode &SceneObject::createNode(
		const vector<pair<shared_ptr<VertexArray>, shared_ptr<Material>>> &meshDataList,
		const bool setAsRoot, const string_view &name) noexcept
	{
		unordered_set<unique_ptr<Mesh>> meshes;

		for (const auto &[pVertexArray, pMaterial] : meshDataList)
			meshes.emplace(make_unique<Mesh>(pVertexArray, __pModelMatrixBuffer, pMaterial, createBoneManager()));

		Joint *const pJoint =
			__joints.emplace_back(make_unique<Joint>(__animMgr, name)).get();

		pJoint->addObserver(this);

		SceneObjectNode *const pNode =
			__nodes.emplace_back(make_unique<SceneObjectNode>(move(meshes), *pJoint, name)).get();

		if (setAsRoot)
			__pRootNode = pNode;

		return *pNode;
	}

	BoneManager &SceneObject::createBoneManager() noexcept
	{
		return *__boneMgrs.emplace_back(make_unique<BoneManager>());
	}

	size_t SceneObject::getNumInstances() const noexcept
	{
		return __pModelMatrixBuffer->getNumInstances();
	}

	void SceneObject::setNumInstances(const GLsizei numInstances) noexcept
	{
		__pModelMatrixBuffer->setNumInstances(numInstances);
	}

	Transform &SceneObject::getTransform(const size_t idx) noexcept
	{
		return __pModelMatrixBuffer->getTransform(idx);
	}

	const Transform &SceneObject::getTransform(const size_t idx) const noexcept
	{
		return __pModelMatrixBuffer->getTransform(idx);
	}

	SceneObjectNode *SceneObject::getNode(const string_view &name) noexcept
	{
		for (const unique_ptr<SceneObjectNode> &pNode : __nodes)
			if (pNode->getName() == name)
				return pNode.get();

		return nullptr;
	}

	const SceneObjectNode *SceneObject::getNode(const string_view &name) const noexcept
	{
		for (const unique_ptr<SceneObjectNode> &pNode : __nodes)
			if (pNode->getName() == name)
				return pNode.get();

		return nullptr;
	}

	AnimationManager &SceneObject::getAnimationManager() noexcept
	{
		return __animMgr;
	}

	const AnimationManager &SceneObject::getAnimationManager() const noexcept
	{
		return __animMgr;
	}

	void SceneObject::update(const float deltaTime) noexcept
	{
		if (!__pRootNode)
			return;

		__pModelMatrixBuffer->updateMatrices();

		Animation &anim = __animMgr.getActiveAnimation();
		anim.adjustTimestamp(deltaTime);

		__pRootNode->update(Constant::Common::IDENTITY_MATRIX);
	}

	void SceneObject::draw() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();
		__pRootNode->draw(getNumInstances());
	}

	void SceneObject::rawDrawcall() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();
		__pRootNode->rawDrawcall(getNumInstances());
	}

	void SceneObject::onUpdateJointMatrix(const string& nodeName, const mat4& jointMatrix) noexcept
	{
		for (const unique_ptr<BoneManager> &pBoneMgr : __boneMgrs)
			pBoneMgr->updateTargetJointMatrices(nodeName, jointMatrix);
	}
}