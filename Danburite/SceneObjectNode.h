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

		void draw(const size_t numInstances = 1ULL) noexcept;
		void rawDrawcall(const size_t numInstances = 1ULL) noexcept;

		template <typename $MaterialQuery>
		void drawIf(const $MaterialQuery query, const size_t numInstances = 1ULL) noexcept;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);

		virtual ~SceneObjectNode() = default;
	};

	constexpr const std::string &SceneObjectNode::getName() const noexcept
	{
		return __name;
	}

	template <typename $MaterialQuery>
	void SceneObjectNode::drawIf(const $MaterialQuery query, const size_t numInstances) noexcept
	{
		__joint.selfDeploy();

		for (const std::unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->drawIf(query, numInstances);

		for (SceneObjectNode *const pChild : __children)
			pChild->drawIf(query, numInstances);
	}

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void SceneObjectNode::traverseMaterial(const FunctionType function, Args &&...args)
	{
		using namespace std;

		static_assert(is_base_of_v<Material, MaterialType>, "MaterialType must be derived from Material.");

		for (const unique_ptr<Mesh> &pMesh : __meshes)
		{
			MaterialType *const pMaterial =
				static_cast<MaterialType *>(pMesh->getMaterial().get());

			if (pMaterial)
				(pMaterial->*function)(std::forward<Args>(args)...);
		}

		for (SceneObjectNode *const pChild : __children)
			pChild->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}
