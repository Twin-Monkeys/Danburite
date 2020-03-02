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
	private:
		static std::shared_ptr<ObjectGL::Texture2D> __loadTexture(
			const std::string &parentPath,
			std::unordered_map<std::string, std::shared_ptr<ObjectGL::Texture2D>> &textureCache,
			const aiMaterial *const pMaterial, const aiTextureType textureType);

		static std::shared_ptr<RenderUnit> __parse(
			const std::string &parentPath,
			const aiNode *const pNode,
			const aiScene *const pScene,
			ObjectGL::UniformSetter &uniformSetter,
			const glm::mat3 &vertexMatrix,
			const glm::mat3 &normalMatrix,
			const MaterialType materialType,
			std::unordered_map<std::string, std::shared_ptr<ObjectGL::Texture2D>> &textureCache);

	public:
		static std::shared_ptr<RenderUnit> import(
			const std::string_view &assetPath,
			ObjectGL::UniformSetter &uniformSetter,
			const glm::mat4 &transformation = Constant::Matrix::IDENTITY_MATRIX,
			const MaterialType materialType = MaterialType::PHONG,
			const std::string &unitName = RenderUnitManager::AUTO_MAPPED_NAME);
	};
}