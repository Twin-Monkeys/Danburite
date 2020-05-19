#include "RenderUnit.h"
#include "RenderUnitManager.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	RenderUnit::RenderUnit(unique_ptr<Mesh> pMesh, const string_view &unitName) noexcept :
		__name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);

		pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.emplace(move(pMesh));
	}

	RenderUnit::RenderUnit(unordered_set<unique_ptr<Mesh>> &&meshes, const string_view &unitName) noexcept :
		__name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer =
			reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);
		
		for (const unique_ptr<Mesh> &pMesh : meshes)
			pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.swap(meshes);
	}

	Transform &RenderUnit::getTransform(const size_t idx) const noexcept
	{
		return __pModelMatrixBuffer->getTransform(idx);
	}

	void RenderUnit::setNumInstances(const GLsizei numInstances) noexcept
	{
		__pModelMatrixBuffer->setNumInstances(numInstances);
		__children.safeTraverse(&RenderUnit::setNumInstances, numInstances);
	}

	void RenderUnit::update(const float deltaTime) noexcept
	{
		__pModelMatrixBuffer->updateMatrix();

		__children.safeTraverse<void(RenderUnit::*)(const float, const vector<mat4> &)>(
			&RenderUnit::update, deltaTime, __pModelMatrixBuffer->getModelMatrices());
	}

	void RenderUnit::update(const float deltaTime, const vector<mat4> &parentModelMatrices) noexcept
	{
		__pModelMatrixBuffer->updateMatrix(parentModelMatrices);

		__children.safeTraverse<void(RenderUnit::*)(const float, const vector<mat4> &)>(
			&RenderUnit::update, deltaTime, __pModelMatrixBuffer->getModelMatrices());
	}

	void RenderUnit::draw() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->draw(GLsizei(NUM_INSTANCES));

		__children.safeTraverse(&RenderUnit::draw);
	}

	void RenderUnit::rawDrawCall() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();

		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->rawDrawCall(GLsizei(NUM_INSTANCES));

		__children.safeTraverse(&RenderUnit::rawDrawCall);
	}
}