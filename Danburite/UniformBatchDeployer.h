#pragma once

#include "UniformSetter.h"
#include "WeakPointerContainer.h"

namespace ObjectGL
{
	class UniformDeployable;

	class UniformBatchDeployer abstract : public UniformSetter
	{
	private:
		WeakPointerContainer<UniformDeployable> __uniformDeployables;

	public:
		void addDeployable(const std::weak_ptr<UniformDeployable> &pUpdatable) noexcept;
		void batchDeploy() noexcept;

		virtual ~UniformBatchDeployer() = default;
	};
}