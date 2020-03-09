#include "RenderUnit.h"
#include "RenderUnitManager.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	RenderUnit::RenderUnit(
		RenderUnitManager &manager, unique_ptr<Mesh> pMesh, const string_view &unitName) noexcept :
		__manager(manager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer = reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);
		pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.emplace(move(pMesh));
	}

	RenderUnit::RenderUnit(
		RenderUnitManager &manager, unordered_set<unique_ptr<Mesh>> &&meshes, const string_view &unitName) noexcept :
		__manager(manager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer = reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);
		
		for (const unique_ptr<Mesh> &pMesh : meshes)
			pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.swap(meshes);
	}

	bool RenderUnit::setName(const string &name) noexcept
	{
		if (name.empty() || (__name == name))
			return false;

		__manager._updateRenderingUnitName(__name, name);
		__name = name;

		return true;
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

	void RenderUnit::addChild(const weak_ptr<RenderUnit> &pChild) noexcept
	{
		__children.add(pChild);
	}

	void RenderUnit::clearChildren() noexcept
	{
		__children.clear();
	}

	void RenderUnit::update() noexcept
	{
		__pModelMatrixBuffer->update();
		__children.safeTraverse<void (RenderUnit::*)(const vector<mat4> &)>
			(&RenderUnit::update, __pModelMatrixBuffer->getModelMatrices());
	}

	void RenderUnit::update(const vector<mat4> &parentModelMatrices) noexcept
	{
		__pModelMatrixBuffer->update(parentModelMatrices);
		__children.safeTraverse<void (RenderUnit::*)(const vector<mat4> &)>
			(&RenderUnit::update, __pModelMatrixBuffer->getModelMatrices());
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