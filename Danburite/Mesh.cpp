#include "Mesh.h"

using namespace std;
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

	void Mesh::updateBones(const glm::mat4 &nodeMatrix) noexcept
	{
		__pBoneMgr->updateMatrics(nodeMatrix);
	}

	void Mesh::draw(const GLsizei numInstances) noexcept
	{
		__pBoneMgr->selfDeploy();

		if (!__pMaterial)
		{
			assert(false);
			return;
		}

		__pMaterial->render(*__pVertexArray, numInstances);
	}

	void Mesh::rawDrawCall(const GLsizei numInstances) noexcept
	{
		__pBoneMgr->selfDeploy();
		__pVertexArray->draw(numInstances);
	}
}