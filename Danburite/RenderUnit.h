#pragma once

#include "Drawable.h"
#include "Mesh.h"
#include <unordered_set>
#include "ModelMatrixBuffer.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class RenderingUnitManager;

	class RenderingUnit : public Updatable, public Drawable
	{
		friend RenderingUnitManager;

	private:
		RenderingUnitManager &__manager;
		std::unordered_set<std::unique_ptr<Mesh>> __meshes;

		std::string __name;

		ObjectGL::WeakPointerContainer<RenderingUnit> __children;
		std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer = std::make_shared<ModelMatrixBuffer>();

		RenderingUnit(const RenderingUnit &) = delete;
		RenderingUnit& operator=(const RenderingUnit &) = delete;

	protected:
		RenderingUnit(
			RenderingUnitManager &manager, std::unique_ptr<Mesh> pMesh, const std::string_view &unitName) noexcept;

		RenderingUnit(
			RenderingUnitManager &manager, std::unordered_set<std::unique_ptr<Mesh>> &&meshes, const std::string_view &unitName) noexcept;

	public:
		const std::string &getName() const noexcept;
		bool setName(const std::string &name) noexcept;

		size_t getNumInstances() const noexcept;
		Transform &getTransform(const size_t idx = 0) const noexcept;

		void setNumInstances(const GLsizei numInstances) noexcept;

		void addChild(const std::weak_ptr<RenderingUnit> &pChild) noexcept;
		void clearChildren() noexcept;

		virtual void update() noexcept override;
		void update(const std::vector<glm::mat4> &parentModelMatrices) noexcept;

		virtual void draw() noexcept override;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);

		virtual ~RenderingUnit() = default;
	};

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void RenderingUnit::traverseMaterial(const FunctionType function, Args &&...args)
	{
		using namespace std;

		static_assert(is_base_of_v<Material, MaterialType>, "MaterialType must be derived from Material.");

		for (const unique_ptr<Mesh> &pMesh : __meshes)
		{
			MaterialType *const pMaterial =
				dynamic_pointer_cast<MaterialType>(pMesh->getMaterial()).get();

			if (pMaterial)
				(pMaterial->*function)(args...);
		}

		__children.safeTraverse(&RenderingUnit::traverseMaterial<MaterialType, FunctionType, Args...>, function, args...);
	}
}
