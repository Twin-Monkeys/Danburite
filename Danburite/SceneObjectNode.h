#pragma once

#include "Mesh.h"
#include <unordered_set>
#include "ModelMatrixBuffer.h"
#include "Joint.h"

namespace Danburite
{
	class SceneObjectNode
	{
	private:
		const std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer;
		JointManager &__jointManager;
		Joint &__joint;

		const std::string __name;

		std::vector<std::unique_ptr<BoneManager>> __boneMgrs;
		std::vector<std::unique_ptr<Mesh>> __meshes;
		std::unordered_set<SceneObjectNode *> __children;

		SceneObjectNode(const SceneObjectNode &) = delete;
		SceneObjectNode& operator=(const SceneObjectNode &) = delete;

	public:
		SceneObjectNode(
			const std::shared_ptr<ModelMatrixBuffer> &pModelMatrixBuffer,
			JointManager &jointManager, const std::string &name) noexcept;

		BoneManager &createBoneManger() noexcept;

		Mesh &createMesh(
			const std::shared_ptr<ObjectGL::VertexArray>& pVertexArray,
			const std::shared_ptr<Material>& pMaterial) noexcept;

		Mesh &createMesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial,
			const BoneManager &boneManager) noexcept;

		constexpr const std::string &getName() const noexcept;

		void addChild(SceneObjectNode &child) noexcept;

		void updateJoint(const glm::mat4 &parentJointMatrix = Constant::Common::IDENTITY_MATRIX) noexcept;
		void updateBones() noexcept;

		void draw(const size_t numInstances) noexcept;
		void rawDrawcall(const size_t numInstances) noexcept;

		template <typename $MaterialType, typename ...$Args>
		void drawUnderMaterialCondition(
			const size_t numInstances, bool($MaterialType::*const memberFunc)($Args ...args) const, $Args ...args) noexcept;

		template <typename $MaterialType, typename $ReturnType, typename ...$Args>
		void traverseMaterial($ReturnType($MaterialType::*const memberFunc)($Args ...args), $Args ...args);

		virtual ~SceneObjectNode() = default;
	};

	constexpr const std::string &SceneObjectNode::getName() const noexcept
	{
		return __name;
	}

	template <typename $MaterialType, typename ...$Args>
	void SceneObjectNode::drawUnderMaterialCondition(
		const size_t numInstances, bool($MaterialType::*const memberFunc)($Args ...args) const, $Args ...args) noexcept
	{
		__joint.selfDeploy();

		for (const std::unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->drawUnderMaterialCondition(numInstances, memberFunc, std::forward<$Args>(args)...);

		for (SceneObjectNode *const pChild : __children)
			pChild->drawUnderMaterialCondition(numInstances, memberFunc, std::forward<$Args>(args)...);
	}

	template <typename $MaterialType, typename $ReturnType, typename ...$Args>
	void SceneObjectNode::traverseMaterial($ReturnType($MaterialType::*const memberFunc)($Args ...args), $Args ...args)
	{
		using namespace std;

		static_assert(is_base_of_v<Material, $MaterialType>, "MaterialType must be derived from Material.");

		for (const unique_ptr<Mesh> &pMesh : __meshes)
		{
			$MaterialType *const pMaterial =
				dynamic_cast<$MaterialType *>(pMesh->getMaterial().get());

			if (pMaterial)
				(pMaterial->*memberFunc)(std::forward<$Args>(args)...);
		}

		for (SceneObjectNode *const pChild : __children)
			pChild->traverseMaterial(memberFunc, std::forward<$Args>(args)...);
	}
}
