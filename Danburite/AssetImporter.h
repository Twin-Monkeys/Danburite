#pragma once

#include "SceneObject.h"
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
		static std::shared_ptr<SceneObject> import(
			const std::string_view &assetPath,
			const glm::mat4 &customTransformationMat = Constant::Common::IDENTITY_MATRIX,
			const MaterialType materialType = MaterialType::PHONG);
	};
}