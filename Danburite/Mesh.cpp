#include "Mesh.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Mesh::Mesh(
		const shared_ptr<VertexArray> &pVertexArray,
		const shared_ptr<Material> &pMaterial,
		std::unique_ptr<BoneOffsetManager> pBoneOffsetManager) noexcept :
		__pVertexArray(pVertexArray), __pMaterial(pMaterial), __pBoneOffsetMgr(move(pBoneOffsetManager))
	{}

	void Mesh::setMaterial(const shared_ptr<Material> &pMaterial) noexcept
	{
		__pMaterial = pMaterial;
	}

	void Mesh::addVertexBuffer(const shared_ptr<VertexBuffer> &pVertexBuffer) noexcept
	{
		__pVertexArray->addVertexBuffer(pVertexBuffer);
	}

	void Mesh::updateBoneMatrices(const Animation &animation) noexcept
	{
		__pBoneOffsetMgr->updateMatrices(animation);
	}

	void Mesh::draw(const GLsizei numInstances) noexcept
	{
		if (!__pMaterial)
		{
			assert(false);
			return;
		}

		__pBoneOffsetMgr->selfDeploy();
		__pMaterial->render(*__pVertexArray, numInstances);
	}

	void Mesh::rawDrawcall(const GLsizei numInstances) noexcept
	{
		if (!__pMaterial)
		{
			assert(false);
			return;
		}

		__pBoneOffsetMgr->selfDeploy();
		__pMaterial->rawDrawcall(*__pVertexArray, numInstances);
	}
}