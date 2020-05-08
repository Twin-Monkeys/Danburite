#include "AssetImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <stack>
#include "VertexAttributeListFactory.h"
#include "TextureUtil.h"
#include "MonoColorMaterial.h"
#include "PhongMaterial.h"
#include "SilhouetteMaterial.h"
#include "TransparentPhongMaterial.h"
#include "ReflectionMaterial.h"
#include "ReflectionPhongMaterial.h"
#include "RefractionMaterial.h"

using namespace std;
using namespace filesystem;
using namespace glm;
using namespace Assimp;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<Texture2D> AssetImporter::__loadTexture(
		const string &parentPath,
		unordered_map<string, shared_ptr<Texture2D>> &textureCache,
		const aiMaterial* const pMaterial, const aiTextureType textureType)
	{
		const unsigned NUM_TEXTURES = pMaterial->GetTextureCount(textureType);
		if (!NUM_TEXTURES)
			return nullptr;

		aiString aiStr;
		pMaterial->GetTexture(textureType, 0, &aiStr);

		string fileName = aiStr.C_Str();
		shared_ptr<Texture2D> &pRetVal = textureCache[fileName];

		if (!pRetVal)
		{
			const string &texPath = (parentPath + '/' + fileName);

			pRetVal = TextureUtil::createTexture2DFromImage(texPath);
			pRetVal->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
			pRetVal->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		}

		return pRetVal;
	}

	template <typename T>
	static void __setupPhongStyleMaterial(
		const shared_ptr<T> &pMaterial,
		const shared_ptr<Texture2D> &pAmbientTex,
		const shared_ptr<Texture2D> &pDiffuseTex,
		const shared_ptr<Texture2D> &pSpecularTex,
		const shared_ptr<Texture2D> &pEmissiveTex,
		const shared_ptr<Texture2D> &pShininessTex,
		const shared_ptr<Texture2D> &pAlphaTex,
		const shared_ptr<Texture2D> &pNormalTex,
		const shared_ptr<Texture2D> &pHeightTex)
	{
		if (pAmbientTex)
		{
			pMaterial->setAmbientTexture(pAmbientTex);
			pMaterial->useAmbientTexture(true);
		}

		if (pDiffuseTex)
		{
			pMaterial->setDiffuseTexture(pDiffuseTex);
			pMaterial->useDiffuseTexture(true);
		}

		if (pSpecularTex)
		{
			pMaterial->setSpecularTexture(pSpecularTex);
			pMaterial->useSpecularTexture(true);
		}

		if (pEmissiveTex)
		{
			pMaterial->setEmissiveTexture(pEmissiveTex);
			pMaterial->useEmissiveTexture(true);
		}

		if (pShininessTex)
		{
			pMaterial->setShininessTexture(pShininessTex);
			pMaterial->useShininessTexture(true);
		}

		if (pAlphaTex)
		{
			pMaterial->setAlphaTexture(pAlphaTex);
			pMaterial->useAlphaTexture(true);
		}

		if (pNormalTex)
		{
			pMaterial->setNormalTexture(pNormalTex);
			pMaterial->useNormalTexture(true);
		}

		if (pHeightTex)
		{
			pMaterial->setHeightTexture(pHeightTex);
			pMaterial->useHeightTexture(true);
		}
	}

	shared_ptr<RenderUnit> AssetImporter::__parse(
		const string &parentPath, const aiNode *const pNode, const aiScene* const pScene,
		const mat4 &vertexMatrix, const mat3 &normalMatrix, const MaterialType materialType,
		unordered_map<string, shared_ptr<Texture2D>> &textureCache)
	{
		RenderUnitManager &renderingUnitMgr = RenderUnitManager::getInstance();
		const aiMesh *const *const pAiMeshes = pScene->mMeshes;
		const aiMaterial *const *const pAiMaterials = pScene->mMaterials;

		unordered_set<unique_ptr<Mesh>> meshes;
		for (unsigned i = 0; i < pNode->mNumMeshes; i++)
		{
			const unsigned MESH_IDX = pNode->mMeshes[i];
			const aiMesh* const pAiMesh = pAiMeshes[MESH_IDX];

			VertexAttributeFlag vertexFlag = VertexAttributeFlag::NONE;

			if (pAiMesh->HasPositions())
				vertexFlag |= VertexAttributeFlag::POS;

			if (pAiMesh->HasVertexColors(0))
				vertexFlag |= VertexAttributeFlag::COLOR;

			if (pAiMesh->HasNormals())
				vertexFlag |= VertexAttributeFlag::NORMAL;

			if (pAiMesh->HasTangentsAndBitangents())
				vertexFlag |= VertexAttributeFlag::TANGENT;

			/*
				a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
				use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			*/
			if (pAiMesh->HasTextureCoords(0))
				vertexFlag |= VertexAttributeFlag::TEXCOORD;

			vector<GLfloat> vertices;
			for (unsigned j = 0; j < pAiMesh->mNumVertices; j++)
			{
				if (vertexFlag & VertexAttributeFlag::POS)
				{
					const aiVector3D &aiPos = pAiMesh->mVertices[j];
					const vec3 &pos = vec3 { vertexMatrix * (vec4 {aiPos.x, aiPos.y, aiPos.z, 1.f}) };

					vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });
				}

				if (vertexFlag & VertexAttributeFlag::COLOR)
				{
					const aiColor4D &color = pAiMesh->mColors[0][j];
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });
				}

				if (vertexFlag & VertexAttributeFlag::NORMAL)
				{
					const aiVector3D &aiNormal = pAiMesh->mNormals[j];
					const vec3 &normal = (normalMatrix * (vec3 { aiNormal.x, aiNormal.y, aiNormal.z }));

					vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });
				}

				if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				{
					const aiVector3D &texCoord = pAiMesh->mTextureCoords[0][j];
					vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
				}

				if (vertexFlag & VertexAttributeFlag::TANGENT)
				{
					const aiVector3D &aiTangent = pAiMesh->mTangents[j];
					const vec3 &tangent = (normalMatrix * (vec3 { aiTangent.x, aiTangent.y, aiTangent.z }));
					vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
				}
			}

			const vector<VertexAttribute> &attribList = VertexAttributeListFactory::getInstance(vertexFlag);

			const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
			pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
			pVertexBuffer->setAttributes(attribList);


			//// Index ////

			vector<GLuint> indices;
			for (unsigned j = 0; j < pAiMesh->mNumFaces; j++)
			{
				const aiFace &face = pAiMesh->mFaces[j];

				for (unsigned k = 0; k < face.mNumIndices; k++)
					indices.emplace_back(face.mIndices[k]);
			}

			const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
			pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

			const shared_ptr<VertexArray> &pVertexArray =
				make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));


			//// Material ////

			const unsigned MATERIAL_IDX = pAiMesh->mMaterialIndex;
			const aiMaterial* const pAiMaterial = pAiMaterials[MATERIAL_IDX];

			shared_ptr<Material> pMaterial = nullptr;
			switch (materialType)
			{
			case MaterialType::MONO_COLOR:
				pMaterial = make_shared<MonoColorMaterial>(vertexFlag);
				break;

			case MaterialType::EXPLODING_PHONG:
				[[fallthrough]];

			case MaterialType::REFLECTION_PHONG:
				[[fallthrough]];

			case MaterialType::TRANSPARENT_PHONG:
				[[fallthrough]];

			case MaterialType::PHONG:
			{
				const shared_ptr<Texture2D> &pAmbientTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_AMBIENT);

				const shared_ptr<Texture2D> &pDiffuseTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_DIFFUSE);

				const shared_ptr<Texture2D> &pSpecularTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_SPECULAR);

				const shared_ptr<Texture2D> &pEmissiveTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_EMISSIVE);

				const shared_ptr<Texture2D> &pShininessTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_SHININESS);

				const shared_ptr<Texture2D> &pAlphaTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_OPACITY);

				const shared_ptr<Texture2D> &pNormalTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_NORMALS);

				const shared_ptr<Texture2D> &pHeightTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_HEIGHT);
				
				if (materialType == MaterialType::REFLECTION_PHONG)
				{
					pMaterial = make_shared<ReflectionPhongMaterial>(vertexFlag);

					__setupPhongStyleMaterial(
						static_pointer_cast<ReflectionPhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex,
						pShininessTex, pAlphaTex, pNormalTex, pHeightTex);
				}
				else if (materialType == MaterialType::TRANSPARENT_PHONG)
				{
					pMaterial = make_shared<TransparentPhongMaterial>(vertexFlag);

					__setupPhongStyleMaterial(
						static_pointer_cast<TransparentPhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex,
						pShininessTex, pAlphaTex, pNormalTex, pHeightTex);
				}
				else
				{
					pMaterial = make_shared<PhongMaterial>(vertexFlag);

					__setupPhongStyleMaterial(
						static_pointer_cast<PhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex,
						pShininessTex, pAlphaTex, pNormalTex, pHeightTex);
				}
			}
				break;

			case MaterialType::SILHOUETTE:
				pMaterial = make_shared<SilhouetteMaterial>(vertexFlag);
				break;

			case MaterialType::REFLECTION:
			{
				const shared_ptr<ReflectionMaterial> &pReflectionMaterial = make_shared<ReflectionMaterial>(vertexFlag);

				const shared_ptr<Texture2D> &pNormalTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_NORMALS);

				if (pNormalTex)
				{
					pReflectionMaterial->setNormalTexture(pNormalTex);
					pReflectionMaterial->useNormalTexture(true);
				}

				pMaterial = pReflectionMaterial;
			}
				break;

			case MaterialType::REFRACTION:
			{
				const shared_ptr<RefractionMaterial> &pRefractionMaterial = make_shared<RefractionMaterial>(vertexFlag);

				const shared_ptr<Texture2D> &pNormalTex =
					__loadTexture(parentPath, textureCache, pAiMaterial, aiTextureType::aiTextureType_NORMALS);

				if (pNormalTex)
				{
					pRefractionMaterial->setNormalTexture(pNormalTex);
					pRefractionMaterial->useNormalTexture(true);
				}

				pMaterial = pRefractionMaterial;
			}
				break;
			}
			
			unique_ptr<Mesh> pMesh = make_unique<Mesh>(pVertexArray, pMaterial);
			meshes.emplace(move(pMesh));
		}

		return renderingUnitMgr.createRenderUnit(move(meshes), pNode->mName.C_Str());
	}

	shared_ptr<RenderUnit> AssetImporter::import(
		const string_view &assetPath,
		const mat4 &transformation,
		const MaterialType materialType,
		const string &unitName)
	{
		Assimp::Importer importer;

		const aiScene* const pScene = importer.ReadFile(
			assetPath.data(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);

		if (!pScene || (pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !(pScene->mRootNode))
			throw AssetImporterException(importer.GetErrorString());

		const string &parentPath = path(assetPath).parent_path().string();
		unordered_map<string, shared_ptr<Texture2D>> textureCache;

		const mat3 normalMatrix = transpose(inverse(mat3 { transformation }));

		// <parent(unit), child(node)> pair stack
		stack<pair<const shared_ptr<RenderUnit>, const aiNode *>> nodeStack;
		nodeStack.emplace(nullptr, pScene->mRootNode);

		shared_ptr<RenderUnit> retVal = nullptr;
		while (!nodeStack.empty())
		{
			const auto [pParent, pChild] = nodeStack.top();
			nodeStack.pop();

			const shared_ptr<RenderUnit> &pParsedChild = __parse(
				parentPath, pChild, pScene, transformation, normalMatrix, materialType, textureCache);

			if (!pParent)
				retVal = pParsedChild;
			else
				pParent->getChildren().add(pParsedChild);

			for (unsigned i = 0; i < pChild->mNumChildren; i++)
				nodeStack.emplace(pParsedChild, pChild->mChildren[i]);
		}

		retVal->setName(unitName);
		return retVal;
	}
}