#pragma once

#include "UniformSetter.h"

namespace ObjectGL
{
	class UniformDeployable abstract
	{
		friend class UniformDeployer;

	protected:
		virtual void _onDeploy(UniformSetter &uniformSetter) noexcept = 0;

	public:
		virtual ~UniformDeployable() = default;
	};
}