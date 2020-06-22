#include "RenderUnitManager.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	string RenderUnitManager::__buildAutoRenderingUnitName() const noexcept
	{
		string retVal = "obj";
		retVal += to_string(__unitCount);

		return retVal;
	}

	shared_ptr<RenderUnit> RenderUnitManager::createRenderUnit(
		unique_ptr<Mesh> &&pMesh,
		const mat4 &nodeTransformationMat,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string &unitName)
	{
		string validName = unitName;
		if (validName == AUTO_MAPPED_NAME)
			validName = __buildAutoRenderingUnitName();

		const shared_ptr<RenderUnit> pRetVal =
			shared_ptr<RenderUnit>(new RenderUnit(move(pMesh), nodeTransformationMat, pAnimationManager, validName));

		__unitCount++;

		return pRetVal;
	}

	shared_ptr<RenderUnit> RenderUnitManager::createRenderUnit(
		unordered_set<unique_ptr<Mesh>> &&meshes,
		const mat4 &nodeTransformationMat,
		const shared_ptr<AnimationManager> &pAnimationManager,
		const string &unitName)
	{
		string validName = unitName;

		if (validName == AUTO_MAPPED_NAME)
			validName = move(__buildAutoRenderingUnitName());

		const shared_ptr<RenderUnit> pRetVal =
			shared_ptr<RenderUnit>(new RenderUnit(move(meshes), nodeTransformationMat, pAnimationManager, validName));

		__unitCount++;

		return pRetVal;
	}

	shared_ptr<RenderUnit> RenderUnitManager::getRenderUnit(const string &name) const noexcept
	{
			return nullptr;
	}
}