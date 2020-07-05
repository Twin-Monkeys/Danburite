#include "SceneObject.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObject::SceneObject() noexcept :
		__jointMgr(__animMgr)
	{}

	SceneObjectNode &SceneObject::createNode(const bool setAsRoot, const string &name) noexcept
	{
		SceneObjectNode* const pNode =
			__nodes.emplace_back(make_unique<SceneObjectNode>(__pModelMatrixBuffer, __jointMgr, name)).get();

		__nameToNodeMap.emplace(name, pNode);

		if (setAsRoot)
			__pRootNode = pNode;

		return *pNode;
	}

	SceneObjectNode& SceneObject::createNode(
		const shared_ptr<VertexArray>& pVertexArray, const shared_ptr<Material>& pMaterial,
		const bool setAsRoot, const string &name) noexcept
	{
		SceneObjectNode &retVal = createNode(setAsRoot, name);
		retVal.createMesh(pVertexArray, pMaterial);

		return retVal;
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

	SceneObjectNode *SceneObject::getNode(const string &name) noexcept
	{
		auto resultIt = __nameToNodeMap.find(name);
		if (resultIt == __nameToNodeMap.end())
			return nullptr;

		return resultIt->second;
	}

	const SceneObjectNode *SceneObject::getNode(const string &name) const noexcept
	{
		auto resultIt = __nameToNodeMap.find(name);
		if (resultIt == __nameToNodeMap.end())
			return nullptr;

		return resultIt->second;
	}

	void SceneObject::update(const float deltaTime) noexcept
	{
		__pModelMatrixBuffer->updateMatrices();

		Animation &anim = __animMgr.getActiveAnimation();
		anim.adjustTimestamp(deltaTime);

		__pRootNode->updateJoint();
		__pRootNode->updateBones();
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
}