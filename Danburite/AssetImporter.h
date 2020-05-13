#pragma once

#include "RenderUnitManager.h"
#include "AssetImporterException.h"
#include <string_view>
#include "Constant.h"
#include "Texture2D.h"

struct aiNode;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

namespace Danburite
{
	class AssetImporter abstract
	{
	public:
		static std::shared_ptr<RenderUnit> import(
			const std::string_view &assetPath,
			const glm::mat4 &transformation = Constant::Matrix::IDENTITY_MATRIX,
			const MaterialType materialType = MaterialType::PHONG,
			const std::string &unitName = RenderUnitManager::AUTO_MAPPED_NAME);
	};
}