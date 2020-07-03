#include "SceneObjectNode.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SceneObjectNode::SceneObjectNode(
		unordered_set<unique_ptr<Mesh>> &&meshes, Joint &joint, const string_view &name) noexcept :
		__joint(joint), __name(name)
	{
		__meshes.swap(meshes);
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
		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->updateBoneMatrices(__joint.getMatrix());

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