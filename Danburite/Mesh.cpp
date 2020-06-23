#include "Mesh.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Mesh::Mesh(
		const shared_ptr<VertexArray> &pVertexArray,
		const shared_ptr<Material> &pMaterial,
		std::unique_ptr<BoneManager> pBoneManager) noexcept :
		__pVertexArray(pVertexArray), __pMaterial(pMaterial), __pBoneMgr(move(pBoneManager))
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
		__pBoneMgr->updateMatrices(animation);
	}

	void Mesh::draw(const GLsizei numInstances) noexcept
	{
		if (!__pMaterial)
		{
			assert(false);
			return;
		}

		__pBoneMgr->selfDeploy();
		__pMaterial->render(*__pVertexArray, numInstances);
	}

	void Mesh::rawDrawcall(const GLsizei numInstances) noexcept
	{
		if (!__pMaterial)
		{
			assert(false);
			return;
		}

		__pBoneMgr->selfDeploy();
		__pMaterial->rawDrawcall(*__pVertexArray, numInstances);
	}
}