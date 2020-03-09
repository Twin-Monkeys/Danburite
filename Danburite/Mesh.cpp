#include "Mesh.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Mesh::Mesh(
		const shared_ptr<VertexArray> &pVertexArray,
		const shared_ptr<Material> &pMaterial) noexcept :
		__pVertexArray(pVertexArray), __pMaterial(pMaterial)
	{}

	void Mesh::setMaterial(const shared_ptr<Material> &pMaterial) noexcept
	{
		__pMaterial = pMaterial;
	}

	void Mesh::addVertexBuffer(const shared_ptr<VertexBuffer> &pVertexBuffer) noexcept
	{
		__pVertexArray->addVertexBuffer(pVertexBuffer);
	}

	void Mesh::draw(const GLsizei numInstances) noexcept
	{
		if (!__pMaterial)
		{
			assert(false);
			return;
		}

		rawDrawCall(numInstances);
	}

	void Mesh::rawDrawCall(const GLsizei numInstances) noexcept
	{
		__pMaterial->render(*__pVertexArray, numInstances);
	}
}