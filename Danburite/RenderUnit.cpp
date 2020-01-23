#include "RenderUnit.h"
#include "RenderUnitManager.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	RenderingUnit::RenderingUnit(
		RenderingUnitManager &manager, unique_ptr<Mesh> pMesh, const string_view &unitName) noexcept :
		__manager(manager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer = reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);
		pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.emplace(move(pMesh));
	}

	RenderingUnit::RenderingUnit(
		RenderingUnitManager &manager, unordered_set<unique_ptr<Mesh>> &&meshes, const string_view &unitName) noexcept :
		__manager(manager), __name(unitName)
	{
		const shared_ptr<VertexBuffer> &pModelMatrixBuffer = reinterpret_pointer_cast<ObjectGL::VertexBuffer>(__pModelMatrixBuffer);
		
		for (const unique_ptr<Mesh> &pMesh : meshes)
			pMesh->addVertexBuffer(pModelMatrixBuffer);

		__meshes.swap(meshes);
	}

	const string &RenderingUnit::getName() const noexcept
	{
		return __name;
	}

	bool RenderingUnit::setName(const string &name) noexcept
	{
		if (name.empty() || (__name == name))
			return false;

		__manager._updateRenderingUnitName(__name, name);
		__name = name;

		return true;
	}

	size_t RenderingUnit::getNumInstances() const noexcept
	{
		return __pModelMatrixBuffer->getNumInstances();
	}

	Transform &RenderingUnit::getTransform(const size_t idx) const noexcept
	{
		return __pModelMatrixBuffer->getTransform(idx);
	}

	void RenderingUnit::setNumInstances(const GLsizei numInstances) noexcept
	{
		__pModelMatrixBuffer->setNumInstances(numInstances);
		__children.safeTraverse(&RenderingUnit::setNumInstances, numInstances);
	}

	void RenderingUnit::addChild(const weak_ptr<RenderingUnit> &pChild) noexcept
	{
		__children.add(pChild);
	}

	void RenderingUnit::clearChildren() noexcept
	{
		__children.clear();
	}

	void RenderingUnit::update() noexcept
	{
		__pModelMatrixBuffer->update();
		__children.safeTraverse<void (RenderingUnit::*)(const vector<mat4> &)>
			(&RenderingUnit::update, __pModelMatrixBuffer->getModelMatrices());
	}

	void RenderingUnit::update(const vector<mat4> &parentModelMatrices) noexcept
	{
		__pModelMatrixBuffer->update(parentModelMatrices);
		__children.safeTraverse<void (RenderingUnit::*)(const vector<mat4> &)>
			(&RenderingUnit::update, __pModelMatrixBuffer->getModelMatrices());
	}

	void RenderingUnit::draw() noexcept
	{
		__pModelMatrixBuffer->selfDeploy();

		const size_t NUM_INSTANCES = __pModelMatrixBuffer->getNumInstances();
		for (const unique_ptr<Mesh> &pMesh : __meshes)
			pMesh->draw(GLsizei(NUM_INSTANCES));

		__children.safeTraverse(&RenderingUnit::draw);
	}
}