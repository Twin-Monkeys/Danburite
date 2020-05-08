#pragma once

#include "Drawable.h"
#include "Mesh.h"
#include <unordered_set>
#include "ModelMatrixBuffer.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class RenderUnitManager;

	class RenderUnit : public Updatable, public Drawable
	{
		friend RenderUnitManager;

	private:
		RenderUnitManager &__manager;
		std::unordered_set<std::unique_ptr<Mesh>> __meshes;

		std::string __name;

		ObjectGL::WeakPointerContainer<RenderUnit> __children;
		std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer = std::make_shared<ModelMatrixBuffer>();

		RenderUnit(const RenderUnit &) = delete;
		RenderUnit& operator=(const RenderUnit &) = delete;

	protected:
		RenderUnit(
			RenderUnitManager &manager,
			std::unique_ptr<Mesh> pMesh,
			const std::string_view &unitName) noexcept;

		RenderUnit(
			RenderUnitManager &manager,
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes,
			const std::string_view &unitName) noexcept;

	public:
		constexpr const std::string &getName() const noexcept;
		bool setName(const std::string &name) noexcept;

		constexpr size_t getNumInstances() const noexcept;
		Transform &getTransform(const size_t idx = 0) const noexcept;

		void setNumInstances(const GLsizei numInstances) noexcept;

		constexpr ObjectGL::WeakPointerContainer<RenderUnit> &getChildren() noexcept;
		constexpr const ObjectGL::WeakPointerContainer<RenderUnit> &getChildren() const noexcept;

		virtual void update(const float deltaTime) noexcept override;
		void update(const float deltaTime, const std::vector<glm::mat4> &parentModelMatrices) noexcept;

		virtual void draw() noexcept override;
		virtual void rawDrawCall() noexcept override;

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

	constexpr ObjectGL::WeakPointerContainer<RenderUnit> &RenderUnit::getChildren() noexcept
	{
		return __children;
	}

	constexpr const ObjectGL::WeakPointerContainer<RenderUnit> &RenderUnit::getChildren() const noexcept
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

		__children.safeTraverse(
			&RenderUnit::traverseMaterial<MaterialType, FunctionType, Args...>,
			function, std::forward<Args>(args)...);
	}
}
