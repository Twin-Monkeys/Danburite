#pragma once

#include "Light.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class LightDeployer
	{
	private:
		ObjectGL::WeakPointerContainer<Light> __lights;

	public:
		void addLight(const std::weak_ptr<Light> &pLight) noexcept;
		void batchDeploy() noexcept;
	};
}