#pragma once

#include "RenderUnit.h"

namespace Danburite
{
	class RenderingUnitManager
	{
		friend RenderingUnit;

	private:
		size_t __unitCount = 0;
		std::unordered_map<std::string, std::shared_ptr<RenderingUnit>> __renderingUnitMap;

		RenderingUnitManager() = default;
		RenderingUnitManager(const RenderingUnitManager &) = delete;
		RenderingUnitManager& operator=(const RenderingUnitManager &) = delete;

		std::string __buildAutoRenderingUnitName() const noexcept;

	protected:
		void _updateRenderingUnitName(const std::string &oldName, const std::string &newName) noexcept;

	public:
		static inline const std::string AUTO_MAPPED_NAME = "";

		std::shared_ptr<RenderingUnit> createRenderingUnit(
			std::unique_ptr<Mesh> pMesh, const std::string &unitName = AUTO_MAPPED_NAME);

		std::shared_ptr<RenderingUnit> createRenderingUnit(
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes, const std::string &unitName = AUTO_MAPPED_NAME);

		std::shared_ptr<RenderingUnit> getRenderingUnit(const std::string &name) const noexcept;
		virtual ~RenderingUnitManager() = default;

		static RenderingUnitManager &getInstance() noexcept;
	};
}