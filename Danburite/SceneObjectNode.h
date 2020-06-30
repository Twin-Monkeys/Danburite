#pragma once

#include "Mesh.h"
#include <unordered_set>
#include "ModelMatrixBuffer.h"
#include "Joint.h"

namespace Danburite
{
	class SceneObjectNode : public Updatable
	{
	private:
		std::unordered_set<std::unique_ptr<Mesh>> __meshes;
		Joint *const __pJoint;
		const std::string __name;

		std::unordered_set<SceneObjectNode *> __children;

		SceneObjectNode(const SceneObjectNode &) = delete;
		SceneObjectNode& operator=(const SceneObjectNode &) = delete;

		void __updateHierarchical_withAnim(const std::vector<glm::mat4>& parentModelMatrices) noexcept;
		void __updateHierarchical_withoutAnim(const std::vector<glm::mat4> &parentModelMatrices) noexcept;

		void __updateBoneMatricesHierarchical() noexcept;

	public:
		SceneObjectNode(
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes,
			Joint *const pJoint, const std::string_view &name) noexcept;

		constexpr const std::string &getName() const noexcept;

		void addChild(SceneObjectNode *const pChild) noexcept;

		virtual void update(const float deltaTime) noexcept override;

		void draw() noexcept;
		void rawDrawcall() noexcept;

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

		for (const shared_ptr<SceneObjectNode> &child : __children)
			child->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}
