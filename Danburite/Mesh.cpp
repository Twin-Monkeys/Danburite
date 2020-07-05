#include "Mesh.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Mesh::Mesh(
		const shared_ptr<VertexArray>& pVertexArray,
		const shared_ptr<Material>& pMaterial,
		const shared_ptr<ModelMatrixBuffer>& pModelMatrixBuffer,
		const BoneManager &boneManager) noexcept :
		__pVertexArray(pVertexArray), __pMaterial(pMaterial), __boneMgr(boneManager)
	{
		__pVertexArray->addVertexBuffer(reinterpret_pointer_cast<VertexBuffer>(pModelMatrixBuffer));
	}

	void Mesh::draw(const GLsizei numInstances) noexcept
	{
		__boneMgr.selfDeploy();
		__pMaterial->render(*__pVertexArray, numInstances);
	}

	void Mesh::rawDrawcall(const GLsizei numInstances) noexcept
	{
		__boneMgr.selfDeploy();
		__pMaterial->rawDrawcall(*__pVertexArray, numInstances);
	}
}