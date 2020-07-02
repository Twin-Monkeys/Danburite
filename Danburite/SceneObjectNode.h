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
		std::unordered_set<std::unique_ptr<Mesh>> __meshes;
		Joint &__joint;
		const std::string __name;

		std::unordered_set<SceneObjectNode *> __children;

		SceneObjectNode(const SceneObjectNode &) = delete;
		SceneObjectNode& operator=(const SceneObjectNode &) = delete;

	public:
		SceneObjectNode(
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes,
			Joint &joint, const std::string_view &name) noexcept;

		constexpr const std::string &getName() const noexcept;

		void addChild(SceneObjectNode &child) noexcept;

		void updateJoint(const glm::mat4 &parentJointMatrix = Constant::Common::IDENTITY_MATRIX) noexcept;
		void updateBones() noexcept;

		void draw(const size_t numInstances) noexcept;
		void rawDrawcall(const size_t numInstances) noexcept;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);

		virtual ~SceneObjectNode() = default;
	};

	constexpr const std::string &SceneObjectNode::getName() const noexcept
	{
		return __name;
	}

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void SceneObjectNode::traverseMaterial(const FunctionType function, Args &&...args)
	{
		using namespace std;

		static_assert(is_base_of_v<Material, MaterialType>, "MaterialType must be derived from Material.");

		for (const unique_ptr<Mesh> &pMesh : __meshes)
		{
			MaterialType *const pMaterial =
				dynamic_pointer_cast<MaterialType>(pMesh->getMaterial()).get();

			if (pMaterial)
				(pMaterial->*function)(std::forward<Args>(args)...);
		}

		for (SceneObjectNode *const pChild : __children)
			pChild->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}
