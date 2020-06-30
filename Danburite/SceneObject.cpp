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
			meshes.emplace(make_unique<Mesh>(pVertexArray, __pModelMatrixBuffer, pMaterial, &createBoneManager()));

		SceneObjectNode *const pNode =
			__nodes.emplace_back(make_unique<SceneObjectNode>(move(meshes), name)).get();

		if (setAsRoot)
			__pRootNode = pNode;

		return *pNode;
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
		return *__pAnimManager;
	}

	const AnimationManager &SceneObject::getAnimationManager() const noexcept
	{
		return *__pAnimManager;
	}

	void SceneObject::update(const float deltaTime) noexcept
	{

	}

	void SceneObject::draw() noexcept
	{

	}

	void SceneObject::rawDrawcall() noexcept
	{
		
	}
}