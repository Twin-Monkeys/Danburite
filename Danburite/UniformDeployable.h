#pragma once

namespace ObjectGL
{
	class UniformBatchDeployer;
	class UniformSetter;

	class UniformDeployable abstract
	{
		friend UniformBatchDeployer;
		friend UniformSetter;

	protected:
		virtual void _onDeploy(UniformSetter &uniformSetter) const noexcept = 0;

	public:
		virtual ~UniformDeployable() = default;
	};
}