#include "RenderUnitManager.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	string RenderingUnitManager::__buildAutoRenderingUnitName() const noexcept
	{
		string retVal = "obj";
		retVal += to_string(__unitCount);

		return retVal;
	}

	void RenderingUnitManager::_updateRenderingUnitName(const string &oldName, const string &newName) noexcept
	{
		__renderingUnitMap.extract(oldName).key() = newName;
	}

	shared_ptr<RenderingUnit> RenderingUnitManager::createRenderingUnit(unique_ptr<Mesh> pMesh, const string &unitName)
	{
		string validName = unitName;
		if (validName == AUTO_MAPPED_NAME)
			validName = __buildAutoRenderingUnitName();

		const shared_ptr<RenderingUnit> pRetVal =
			shared_ptr<RenderingUnit>(new RenderingUnit(*this, move(pMesh), validName));

		__renderingUnitMap.emplace(validName, pRetVal);
		__unitCount++;

		return pRetVal;
	}

	shared_ptr<RenderingUnit> RenderingUnitManager::createRenderingUnit(unordered_set<unique_ptr<Mesh>> &&meshes, const string &unitName)
	{
		string validName = unitName;
		if (validName == AUTO_MAPPED_NAME)
			validName = __buildAutoRenderingUnitName();

		const shared_ptr<RenderingUnit> pRetVal =
			shared_ptr<RenderingUnit>(new RenderingUnit(*this, move(meshes), validName));

		__renderingUnitMap.emplace(validName, pRetVal);
		__unitCount++;

		return pRetVal;
	}

	shared_ptr<RenderingUnit> RenderingUnitManager::getRenderingUnit(const string &name) const noexcept
	{
		auto result = __renderingUnitMap.find(name);
		AssertException::test(result != __renderingUnitMap.end());

		return result->second;
	}

	RenderingUnitManager &RenderingUnitManager::getInstance() noexcept
	{
		static RenderingUnitManager instance;
		return instance;
	}
}