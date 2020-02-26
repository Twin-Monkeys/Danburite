#include "RenderUnitManager.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	string RenderUnitManager::__buildAutoRenderingUnitName() const noexcept
	{
		string retVal = "obj";
		retVal += to_string(__unitCount);

		return retVal;
	}

	void RenderUnitManager::_updateRenderingUnitName(const string &oldName, const string &newName) noexcept
	{
		__renderUnitMap.extract(oldName).key() = newName;
	}

	shared_ptr<RenderUnit> RenderUnitManager::createRenderUnit(unique_ptr<Mesh> pMesh, const string &unitName)
	{
		string validName = unitName;
		if (validName == AUTO_MAPPED_NAME)
			validName = __buildAutoRenderingUnitName();

		const shared_ptr<RenderUnit> pRetVal =
			shared_ptr<RenderUnit>(new RenderUnit(*this, move(pMesh), validName));

		__renderUnitMap.emplace(validName, pRetVal);
		__unitCount++;

		return pRetVal;
	}

	shared_ptr<RenderUnit> RenderUnitManager::createRenderUnit(unordered_set<unique_ptr<Mesh>> &&meshes, const string &unitName)
	{
		string validName = unitName;
		if (validName == AUTO_MAPPED_NAME)
			validName = __buildAutoRenderingUnitName();

		const shared_ptr<RenderUnit> pRetVal =
			shared_ptr<RenderUnit>(new RenderUnit(*this, move(meshes), validName));

		__renderUnitMap.emplace(validName, pRetVal);
		__unitCount++;

		return pRetVal;
	}

	shared_ptr<RenderUnit> RenderUnitManager::getRenderUnit(const string &name) const noexcept
	{
		auto result = __renderUnitMap.find(name);
		if (result == __renderUnitMap.end())
			return nullptr;

		return result->second;
	}
}