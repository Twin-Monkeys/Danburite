#pragma once

#include "RenderUnit.h"

namespace Danburite
{
	class RenderUnitManager
	{
		friend RenderUnit;

	private:
		size_t __unitCount = 0;
		std::unordered_map<std::string, std::shared_ptr<RenderUnit>> __renderUnitMap;

		RenderUnitManager() = default;
		RenderUnitManager(const RenderUnitManager &) = delete;
		RenderUnitManager& operator=(const RenderUnitManager &) = delete;

		std::string __buildAutoRenderingUnitName() const noexcept;

	protected:
		void _updateRenderingUnitName(const std::string &oldName, const std::string &newName) noexcept;

	public:
		static inline const std::string AUTO_MAPPED_NAME = "";

		std::shared_ptr<RenderUnit> createRenderUnit(
			std::unique_ptr<Mesh> pMesh, const std::string &unitName = AUTO_MAPPED_NAME);

		std::shared_ptr<RenderUnit> createRenderUnit(
			std::unordered_set<std::unique_ptr<Mesh>> &&meshes, const std::string &unitName = AUTO_MAPPED_NAME);

		std::shared_ptr<RenderUnit> getRenderUnit(const std::string &name) const noexcept;
		virtual ~RenderUnitManager() = default;

		static RenderUnitManager &getInstance() noexcept;
	};
}