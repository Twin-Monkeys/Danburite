#pragma once

namespace ObjectGL
{
	class UniformDeployable abstract
	{
		friend class UniformBatchDeployer;
		friend class UniformSetter;

	protected:
		virtual void _onDeploy(UniformSetter &uniformSetter) noexcept = 0;

	public:
		virtual ~UniformDeployable() = default;
	};
}