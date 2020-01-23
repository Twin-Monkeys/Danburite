#pragma once

#include "SkyboxUniformSetter.h"

namespace Danburite
{
	class SkyboxUniformDeployable abstract
	{
	protected:
		virtual void _onDeploy(SkyboxUniformSetter &target) noexcept = 0;

	public:
		virtual ~SkyboxUniformDeployable() = default;
	};
}