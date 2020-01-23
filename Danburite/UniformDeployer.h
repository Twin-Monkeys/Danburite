#pragma once

#include "UniformSetter.h"
#include "WeakPointerContainer.h"

namespace ObjectGL
{
	class UniformDeployable;

	class UniformDeployer abstract : public UniformSetter
	{
	private:
		WeakPointerContainer<UniformDeployable> __uniformDeployables;

	public:
		void addDeployable(const std::weak_ptr<UniformDeployable> &pUpdatable) noexcept;
		void batchDeploy() noexcept;
		void directDeploy(UniformDeployable &deployable) noexcept;

		virtual ~UniformDeployer() = default;
	};
}