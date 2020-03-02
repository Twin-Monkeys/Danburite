#include "UniformBatchDeployer.h"
#include "UniformDeployable.h"

using namespace std;

namespace ObjectGL
{
	void UniformBatchDeployer::addDeployable(const weak_ptr<UniformDeployable> &pUpdatable) noexcept
	{
		__uniformDeployables.add(pUpdatable);
	}

	void UniformBatchDeployer::batchDeploy() noexcept
	{
		__uniformDeployables.safeTraverse(&UniformDeployable::_onDeploy, *this);
	}
}