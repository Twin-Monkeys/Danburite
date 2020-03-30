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
#include "OutliningPhongMaterial.h"
#include "TransparentPhongMaterial.h"
#include "ReflectionMaterial.h"
#include "ReflectionPhongMaterial.h"
#include "RefractionMaterial.h"
#include "ExplodingPhongMaterial.h"

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
		const shared_ptr<Texture2D> &pNormalTex)
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
	}

	shared_ptr<RenderUnit> AssetImporter::__parse(
		const string &parentPath, const aiNode *const pNode, const aiScene* const pScene,
		const mat3 &vertexMatrix, const mat3 &normalMatrix, const MaterialType materialType,
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

			VertexAttributeType vertexType = VertexAttributeType::NONE;

			if (pAiMesh->HasPositions())
				vertexType |= VertexAttributeFlag::POS3;
			else
				continue;

			if (pAiMesh->HasVertexColors(0))
				vertexType |= VertexAttributeFlag::COLOR4;

			if (pAiMesh->HasNormals())
				vertexType |= VertexAttributeFlag::NORMAL3;


			/*
				a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
				use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			*/
			if (pAiMesh->HasTextureCoords(0))
				vertexType |= VertexAttributeFlag::TEXCOORD2;


			vector<GLfloat> vertices;
			for (unsigned j = 0; j < pAiMesh->mNumVertices; j++)
			{
				if (vertexType & VertexAttributeFlag::POS3)
				{
					const aiVector3D &aiPos = pAiMesh->mVertices[j];
					const vec3 pos = (vertexMatrix * (vec3 {aiPos.x, aiPos.y, aiPos.z}));

					vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });
				}

				if (vertexType & VertexAttributeFlag::COLOR4)
				{
					const aiColor4D &color = pAiMesh->mColors[0][j];
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });
				}

				if (vertexType & VertexAttributeFlag::NORMAL3)
				{
					const aiVector3D &aiNormal = pAiMesh->mNormals[j];
					const vec3 normal = (normalMatrix * (vec3 { aiNormal.x, aiNormal.y, aiNormal.z }));

					vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });
				}

				if (vertexType & VertexAttributeFlag::TEXCOORD2)
				{
					const aiVector3D &texCoord = pAiMesh->mTextureCoords[0][j];
					vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
				}
			}

			const VertexAttributeList &attribList = VertexAttributeListFactory::getInstance(vertexType);

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
				pMaterial = make_shared<MonoColorMaterial>(vertexType);
				break;

			case MaterialType::EXPLODING_PHONG:
				[[fallthrough]];

			case MaterialType::REFLECTION_PHONG:
				[[fallthrough]];

			case MaterialType::TRANSPARENT_PHONG:
				[[fallthrough]];

			case MaterialType::OUTLINING_PHONG:
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
				
				if (materialType == MaterialType::EXPLODING_PHONG)
				{
					pMaterial = make_shared<ExplodingPhongMaterial>(vertexType);

					__setupPhongStyleMaterial(
						static_pointer_cast<ExplodingPhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex, pShininessTex, pAlphaTex, pNormalTex);
				}
				else if (materialType == MaterialType::REFLECTION_PHONG)
				{
					pMaterial = make_shared<ReflectionPhongMaterial>(vertexType);

					__setupPhongStyleMaterial(
						static_pointer_cast<ReflectionPhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex, pShininessTex, pAlphaTex, pNormalTex);
				}
				else if (materialType == MaterialType::TRANSPARENT_PHONG)
				{
					pMaterial = make_shared<TransparentPhongMaterial>(vertexType);

					__setupPhongStyleMaterial(
						static_pointer_cast<TransparentPhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex, pShininessTex, pAlphaTex, pNormalTex);
				}
				else if (materialType == MaterialType::OUTLINING_PHONG)
				{
					pMaterial = make_shared<OutliningPhongMaterial>(vertexType);

					__setupPhongStyleMaterial(
						static_pointer_cast<OutliningPhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex, pShininessTex, pAlphaTex, pNormalTex);
				}
				else
				{
					pMaterial = make_shared<PhongMaterial>(vertexType);

					__setupPhongStyleMaterial(
						static_pointer_cast<PhongMaterial>(pMaterial),
						pAmbientTex, pDiffuseTex, pSpecularTex, pEmissiveTex, pShininessTex, pAlphaTex, pNormalTex);
				}
			}
				break;

			case MaterialType::SILHOUETTE:
				pMaterial = make_shared<SilhouetteMaterial>(vertexType);
				break;

			case MaterialType::REFLECTION:
			{
				const shared_ptr<ReflectionMaterial> &pReflectionMaterial = make_shared<ReflectionMaterial>(vertexType);

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
				const shared_ptr<RefractionMaterial> &pRefractionMaterial = make_shared<RefractionMaterial>(vertexType);

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

		return renderingUnitMgr.createRenderUnit(move(meshes));
	}

	shared_ptr<RenderUnit> AssetImporter::import(
		const string_view &assetPath,
		const mat4 &transformation,
		const MaterialType materialType,
		const string &unitName)
	{
		Assimp::Importer importer;

		const aiScene* const pScene = importer.ReadFile(
			assetPath.data(), aiProcess_Triangulate /*| aiProcess_CalcTangentSpace*/);

		if (!pScene || (pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !(pScene->mRootNode))
			throw AssetImporterException(importer.GetErrorString());

		const string &parentPath = path(assetPath).parent_path().string();
		unordered_map<string, shared_ptr<Texture2D>> textureCache;

		const mat3 vertexMatrix { transformation };
		const mat3 normalMatrix = transpose(inverse(vertexMatrix));

		// <parent(unit), child(node)> pair stack
		stack<pair<const shared_ptr<RenderUnit>, const aiNode *>> nodeStack;
		nodeStack.emplace(nullptr, pScene->mRootNode);

		shared_ptr<RenderUnit> retVal = nullptr;
		while (!nodeStack.empty())
		{
			const auto [pParent, pChild] = nodeStack.top();
			nodeStack.pop();

			const shared_ptr<RenderUnit> &pParsedChild = __parse(
				parentPath, pChild, pScene, vertexMatrix, normalMatrix, materialType, textureCache);

			if (!pParent)
				retVal = pParsedChild;
			else
				pParent->addChild(pParsedChild);

			for (unsigned i = 0; i < pChild->mNumChildren; i++)
				nodeStack.emplace(pParsedChild, pChild->mChildren[i]);
		}

		retVal->setName(unitName);
		return retVal;
	}
}