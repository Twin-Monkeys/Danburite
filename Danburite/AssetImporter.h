#pragma once

#include "RenderUnitManager.h"
#include "AssetImporterException.h"
#include <string_view>
#include "Constant.h"

struct aiNode;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

namespace Danburite
{
	class AssetImporter abstract
	{
	private:
		static std::shared_ptr<ObjectGL::Texture2D> __loadTexture(
			const std::string &parentPath,
			std::unordered_map<std::string, std::shared_ptr<ObjectGL::Texture2D>> &textureCache,
			const aiMaterial *const pMaterial, const aiTextureType textureType);

		static std::shared_ptr<RenderingUnit> __parse(
			const std::string &parentPath,
			const aiNode *const pNode,
			const aiScene *const pScene,
			const glm::mat3 &vertexMatrix,
			const glm::mat3 &normalMatrix,
			const MaterialType materialType,
			std::unordered_map<std::string, std::shared_ptr<ObjectGL::Texture2D>> &textureCache);

	public:
		static std::shared_ptr<RenderingUnit> import(
			const std::string_view &assetPath,
			const glm::mat4 &transformation = Constant::Matrix::IDENTITY_MATRIX,
			const MaterialType materialType = MaterialType::PHONG,
			const std::string &unitName = RenderingUnitManager::AUTO_MAPPED_NAME);
	};
}