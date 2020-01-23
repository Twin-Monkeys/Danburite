#pragma once

#include "MaterialUniformSetter.h"

namespace Danburite
{
	class MaterialUniformDeployable abstract
	{
	protected:
		virtual void _onDeploy(MaterialUniformSetter &target) noexcept = 0;

	public:
		virtual ~MaterialUniformDeployable() = default;
	};
}