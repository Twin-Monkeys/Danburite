#pragma once

#include "LightUniformSetter.h"

namespace Danburite
{
	class LightUniformDeployable abstract
	{
	protected:
		virtual void _onDeploy(LightUniformSetter &target) noexcept = 0;

	public:
		virtual ~LightUniformDeployable() = default;
	};
}