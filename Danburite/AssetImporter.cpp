#include "AssetImporter.h"
#include <assimp/Importer.hpp>		// C++ importer interface
#include <assimp/scene.h>			// Output data structure
#include <assimp/postprocess.h>		// Post processing flags
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
#include <array>
#include "Animation.h"

using namespace std;
using namespace filesystem;
using namespace glm;
using namespace Assimp;
using namespace ObjectGL;

namespace Danburite
{
	static shared_ptr<Texture2D> __loadTexture(
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

	static shared_ptr<RenderUnit> __parseNode(
		const string &parentPath, const aiNode *const pNode, const aiScene* const pScene,
		const mat4 &modelMatrix, const mat3 &normalMatrix, const MaterialType materialType,
		unordered_map<string, shared_ptr<Texture2D>> &textureCache)
	{
		RenderUnitManager &renderingUnitMgr = RenderUnitManager::getInstance();
		const aiMesh *const *const pAiMeshes = pScene->mMeshes;
		const aiMaterial *const *const pAiMaterials = pScene->mMaterials;

		// <bone name, bone idx> map
		unordered_map<string_view, unsigned> boneIdxMap;

		unordered_set<unique_ptr<Mesh>> meshes;
		for (unsigned meshIter = 0U; meshIter < pNode->mNumMeshes; meshIter++)
		{
			const unsigned MESH_IDX = pNode->mMeshes[meshIter];
			const aiMesh* const pAiMesh = pAiMeshes[MESH_IDX];

			// vertex id, bone infomation per vertex (bone idx, bone weight)
			unordered_map<unsigned, vector<pair<unsigned, float>>> vertexBoneInfoMap;

			VertexAttributeFlag vertexFlag = VertexAttributeFlag::POS;

			assert(pAiMesh->HasPositions());

			if (pAiMesh->HasVertexColors(0))
				vertexFlag |= VertexAttributeFlag::COLOR;

			if (pAiMesh->HasNormals())
				vertexFlag |= VertexAttributeFlag::NORMAL;

			/*
				a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
				use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			*/
			if (pAiMesh->HasTextureCoords(0))
				vertexFlag |= VertexAttributeFlag::TEXCOORD;

			if (pAiMesh->HasTangentsAndBitangents())
				vertexFlag |= VertexAttributeFlag::TANGENT;

			if (pAiMesh->HasBones())
			{
				vertexFlag |= VertexAttributeFlag::BONE;

				for (unsigned boneIdx = 0U; boneIdx < pAiMesh->mNumBones; boneIdx++)
				{
					const aiBone *const pBone = pAiMesh->mBones[boneIdx];

					// bone name == node name
					boneIdxMap.emplace(pBone->mName.C_Str(), boneIdx);

					for (unsigned weightIter = 0U; weightIter < pBone->mNumWeights; weightIter++)
					{
						aiVertexWeight &vertexWeight = pBone->mWeights[weightIter];
						vector<pair<unsigned, float>> &bonesPerVertex = vertexBoneInfoMap[vertexWeight.mVertexId];

						if (!glm::epsilonEqual(vertexWeight.mWeight, 0.f, glm::epsilon<float>()))
							bonesPerVertex.emplace_back(boneIdx, vertexWeight.mWeight);
					}
				}

				if (pScene->HasAnimations())
				{
					for (unsigned animIter = 0U; animIter < pScene->mNumAnimations; animIter++)
					{
						const aiAnimation *const pAnim = pScene->mAnimations[animIter];

						for (unsigned keyframeIter = 0U; keyframeIter < pAnim->mNumChannels; keyframeIter++)
						{
							const aiNodeAnim *const pKeyframe = pAnim->mChannels[keyframeIter];
							const unsigned boneIdx = boneIdxMap[pKeyframe->mNodeName.C_Str()];

							const aiBone *const pBone = pAiMesh->mBones[boneIdx];
						}
					}
				}
			}

			vector<GLfloat> vertices;
			for (unsigned vertexIter = 0; vertexIter < pAiMesh->mNumVertices; vertexIter++)
			{
				const aiVector3D &aiPos = pAiMesh->mVertices[vertexIter];
				const vec3 &pos = vec3 { modelMatrix * (vec4 {aiPos.x, aiPos.y, aiPos.z, 1.f}) };

				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });

				if (vertexFlag & VertexAttributeFlag::COLOR)
				{
					const aiColor4D &color = pAiMesh->mColors[0][vertexIter];
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });
				}

				if (vertexFlag & VertexAttributeFlag::NORMAL)
				{
					const aiVector3D &aiNormal = pAiMesh->mNormals[vertexIter];
					const vec3 &normal = (normalMatrix * (vec3 { aiNormal.x, aiNormal.y, aiNormal.z }));

					vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });
				}

				if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				{
					const aiVector3D &texCoord = pAiMesh->mTextureCoords[0][vertexIter];
					vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
				}

				if (vertexFlag & VertexAttributeFlag::TANGENT)
				{
					const aiVector3D &aiTangent = pAiMesh->mTangents[vertexIter];
					const vec3 &tangent = (normalMatrix * (vec3 { aiTangent.x, aiTangent.y, aiTangent.z }));
					vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
				}

				if (vertexFlag & VertexAttributeFlag::BONE)
				{
					vector<pair<unsigned, float>> &bonesPerVertex = vertexBoneInfoMap[vertexIter];
					array<GLfloat, 4ULL> boneIndices { 0.f };
					array<GLfloat, 4ULL> boneWeights { 0.f };

					unsigned numBones = 0U;
					for (const auto &[boneIdx, boneWeight] : bonesPerVertex)
					{
						memcpy(&boneIndices[numBones], &boneIdx, sizeof(GLfloat));
						boneWeights[numBones] = boneWeight;

						numBones++;
						if (numBones >= 4U)
							break;
					}

					vertices.insert(vertices.end(), boneIndices.begin(), boneIndices.end());
					vertices.insert(vertices.end(), boneWeights.begin(), boneWeights.end());

					const aiAnimation *const pAnim = pScene->mAnimations[0];

					// #keyframes
					pAnim->mNumChannels;

					// ÃÊ´ç tick ¼ö
					pAnim->mTicksPerSecond;

					// ÃÑ tick ¼ö
					pAnim->mDuration;

					aiNodeAnim *const pNodeAnim = pAnim->mChannels[0];
				}
			}

			const vector<VertexAttribute> &attribList = VertexAttributeListFactory::getInstance(vertexFlag);

			const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
			pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
			pVertexBuffer->setAttributes(attribList);


			//// Index ////

			vector<GLuint> indices;
			for (unsigned faceIter = 0; faceIter < pAiMesh->mNumFaces; faceIter++)
			{
				const aiFace &face = pAiMesh->mFaces[faceIter];

				for (unsigned indexIter = 0; indexIter < face.mNumIndices; indexIter++)
					indices.emplace_back(face.mIndices[indexIter]);
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
		/*
			The importer manages all the resources for itsself.
			If the importer is destroyed,
			All the data that was created/read by it will be destroyed, too.
		*/
		Assimp::Importer importer;

		/*
			Do not modify any scene data.
			It¡¯s suicide in DLL builds if you try to use new Or delete on any of the arrays in the scene.

			A aiScene forms the root of the data, from here you gain access to all the nodes,
			Meshes, materials, animations or textures that were read from the imported file.

			If you need the imported data to be in a left-handed coordinate system,
			Supply the aiProcess_MakeLeftHanded flag.

			The output face winding is counter clockwise.
			Use aiProcess_FlipWindingOrder to get CW data.
		*/
		const aiScene* const pScene = importer.ReadFile(
			assetPath.data(),
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

		if (!pScene || (pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
			throw AssetImporterException(importer.GetErrorString());

		if (!pScene->mRootNode)
			return nullptr;


		const string &parentPath = path(assetPath).parent_path().string();
		unordered_map<string, shared_ptr<Texture2D>> textureCache;

		/*
			Nodes are little named entities in the scene that have a place
			And orientation relative to their parents.
			Starting from the scene¡¯s root node all nodes can have 0 to x child nodes,
			Thus forming a hierarchy.
			They form the base on which the scene is built on:
			A node can refer to 0..x meshes, can be referred to by a bone of a mesh
			Or can be animated by a key sequence of an animation.
			DirectX calls them "frames", others call them "objects", we call them aiNode.

			A node can potentially refer to single or multiple meshes.
			The meshes are not stored inside the node, but instead in an array of aiMesh inside the aiScene.
			A node only refers to them by their array index.
			This also means that multiple nodes can refer to the same mesh,
			Which provides a simple form of instancing.
			A mesh referred to by this way lives in the node¡¯s local coordinate system.
			If you want the mesh¡¯s orientation in global space,
			You¡¯d have to concatenate the transformations from the referring node and all of its parents.
		*/
		// <parent(RenderUnit), parent matrix(mat4), child(aiNode)> tuple stack
		stack<tuple<shared_ptr<RenderUnit>, mat4, aiNode *>> nodeStack;
		nodeStack.emplace(nullptr, transformation, pScene->mRootNode);

		shared_ptr<RenderUnit> retVal = nullptr;
		while (!nodeStack.empty())
		{
			auto [pParent, transMat, pCurrentNode] = nodeStack.top();
			nodeStack.pop();

			mat4 localTransMat;
			aiMatrix4x4 &aiLocalTransMat = pCurrentNode->mTransformation;
			memcpy(&localTransMat, &aiLocalTransMat.Transpose(), sizeof(mat4));

			transMat *= localTransMat;

			const mat3 &normalMat = transpose(inverse(mat3 { transMat }));

			const shared_ptr<RenderUnit> &pParsedCurrent = __parseNode(
				parentPath, pCurrentNode, pScene, transMat, normalMat, materialType, textureCache);

			if (!pParent)
				retVal = pParsedCurrent;
			else
				pParent->getChildren().add(pParsedCurrent);

			for (unsigned i = 0; i < pCurrentNode->mNumChildren; i++)
				nodeStack.emplace(pParsedCurrent, transMat, pCurrentNode->mChildren[i]);
		}

		retVal->setName(unitName);
		return retVal;

		// Everything will be cleaned up by the importer destructor.
	}
}