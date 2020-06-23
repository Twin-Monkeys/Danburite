#pragma once

#include "Drawable.h"
#include "Mesh.h"
#include <unordered_set>
#include "ModelMatrixBuffer.h"
#include "AnimationManager.h"

namespace Danburite
{
	class RenderUnit : public Updatable, public Drawable
	{
	private:
		std::unordered_set<std::unique_ptr<Mesh>> __meshes;

		const std::string __name;

		std::unordered_set<std::shared_ptr<RenderUnit>> __children;
		const std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer;

		const std::shared_ptr<AnimationManager> __pAnimManager;

		RenderUnit(const RenderUnit &) = delete;
		RenderUnit& operator=(const RenderUnit &) = delete;

		void __updateBoneHierarchical(const glm::mat4& parentNodeMatrix) noexcept;
		void __updateHierarchical_withAnim(const std::vector<glm::mat4> &parentModelMatrices);

		void __updateHierarchical_withoutAnim(const std::vector<glm::mat4> &parentModelMatrices);

	public:
		RenderUnit(
			std::unique_ptr<Mesh> pMesh,
			const glm::mat4 &nodeTransformationMat = glm::mat4 { 1.f },
			const std::shared_ptr<AnimationManager> &pAnimationManager = nullptr,
			const std::string_view &unitName = "") noexcept;

		RenderUnit(
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes,
			const glm::mat4 &nodeTransformationMat = glm::mat4 { 1.f },
			const std::shared_ptr<AnimationManager> &pAnimationManager = nullptr,
			const std::string_view &unitName = "") noexcept;

		constexpr const std::string &getName() const noexcept;

		constexpr size_t getNumInstances() const noexcept;
		Transform &getTransform(const size_t idx = 0) const noexcept;

		void setNumInstances(const GLsizei numInstances) noexcept;

		AnimationManager &getAnimationManager() noexcept;
		const AnimationManager &getAnimationManager() const noexcept;

		constexpr std::unordered_set<std::shared_ptr<RenderUnit>> &getChildren() noexcept;
		constexpr const std::unordered_set<std::shared_ptr<RenderUnit>> &getChildren() const noexcept;

		virtual void update(const float deltaTime) noexcept override;

		virtual void draw() noexcept override;
		virtual void rawDrawcall() noexcept override;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);

		virtual ~RenderUnit() = default;
	};

	constexpr const std::string &RenderUnit::getName() const noexcept
	{
		return __name;
	}

	constexpr size_t RenderUnit::getNumInstances() const noexcept
	{
		return __pModelMatrixBuffer->getNumInstances();
	}

	constexpr std::unordered_set<std::shared_ptr<RenderUnit>> &RenderUnit::getChildren() noexcept
	{
		return __children;
	}

	constexpr const std::unordered_set<std::shared_ptr<RenderUnit>> &RenderUnit::getChildren() const noexcept
	{
		return __children;
	}

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void RenderUnit::traverseMaterial(const FunctionType function, Args &&...args)
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

		for (const shared_ptr<RenderUnit> &child : __children)
			child->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}
