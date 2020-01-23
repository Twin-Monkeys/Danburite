#include "UniformDeployer.h"
#include "UniformDeployable.h"

using namespace std;

namespace ObjectGL
{
	void UniformDeployer::addDeployable(const weak_ptr<UniformDeployable> &pUpdatable) noexcept
	{
		__uniformDeployables.add(pUpdatable);
	}

	void UniformDeployer::batchDeploy() noexcept
	{
		__uniformDeployables.safeTraverse(&UniformDeployable::_onDeploy, *this);
	}

	void UniformDeployer::directDeploy(UniformDeployable &deployable) noexcept
	{
		deployable._onDeploy(*this);
	}
}