#pragma once

#include "SceneObject.h"
#include "AssetImporterException.h"
#include <string_view>

namespace Danburite
{
	class AssetImporter abstract
	{
	public:
		[[nodiscard]]
		static std::shared_ptr<SceneObject> import(
			const std::string_view &assetPath, const MaterialType materialType = MaterialType::PHONG);
	};
}