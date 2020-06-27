#pragma once

#include "Drawable.h"
#include "Mesh.h"
#include <unordered_set>
#include "ModelMatrixBuffer.h"
#include "AnimationManager.h"

namespace Danburite
{
	class SceneObject : public Updatable, public Drawable
	{
	private:
		std::unordered_set<std::unique_ptr<Mesh>> __meshes;

		const std::string __name;

		std::unordered_set<std::shared_ptr<SceneObject>> __children;
		const std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer = std::make_shared<ModelMatrixBuffer>();

		const std::shared_ptr<AnimationManager> __pAnimManager;

		SceneObject(const SceneObject &) = delete;
		SceneObject& operator=(const SceneObject &) = delete;

		void __updateHierarchical_withAnim(const std::vector<glm::mat4>& parentModelMatrices) noexcept;
		void __updateHierarchical_withoutAnim(const std::vector<glm::mat4> &parentModelMatrices) noexcept;

		void __updateBoneMatricesHierarchical() noexcept;

	public:
		SceneObject(
			std::unique_ptr<Mesh> &&pMesh,
			const std::shared_ptr<AnimationManager>& pAnimationManager = nullptr,
			const std::string_view& unitName = "NO_NAMED_OBJ") noexcept;

		SceneObject(
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes,
			const std::shared_ptr<AnimationManager> &pAnimationManager = nullptr,
			const std::string_view &unitName = "NO_NAMED_OBJ") noexcept;

		constexpr const std::string &getName() const noexcept;

		constexpr size_t getNumInstances() const noexcept;
		Transform &getTransform(const size_t idx = 0) const noexcept;

		void setNumInstances(const GLsizei numInstances) noexcept;

		AnimationManager &getAnimationManager() noexcept;
		const AnimationManager &getAnimationManager() const noexcept;

		constexpr std::unordered_set<std::shared_ptr<SceneObject>> &getChildrenSet() noexcept;
		constexpr const std::unordered_set<std::shared_ptr<SceneObject>> &getChildrenSet() const noexcept;

		virtual void update(const float deltaTime) noexcept override;

		virtual void draw() noexcept override;
		virtual void rawDrawcall() noexcept override;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);

		virtual ~SceneObject() = default;
	};

	constexpr const std::string &SceneObject::getName() const noexcept
	{
		return __name;
	}

	constexpr size_t SceneObject::getNumInstances() const noexcept
	{
		return __pModelMatrixBuffer->getNumInstances();
	}

	constexpr std::unordered_set<std::shared_ptr<SceneObject>> &SceneObject::getChildrenSet() noexcept
	{
		return __children;
	}

	constexpr const std::unordered_set<std::shared_ptr<SceneObject>> &SceneObject::getChildrenSet() const noexcept
	{
		return __children;
	}

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void SceneObject::traverseMaterial(const FunctionType function, Args &&...args)
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

		for (const shared_ptr<SceneObject> &child : __children)
			child->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}
