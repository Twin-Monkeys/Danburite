#pragma once

#include "Light.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class LightHandler
	{
	private:
		ObjectGL::WeakPointerContainer<Light> __lights;

	public:
		void addLight(const std::weak_ptr<Light> &pLight) noexcept;
		void batchDeploy() noexcept;
		void batchBakeDepthMap(Drawer &drawer) noexcept;
		void batchVolumeDrawcall() noexcept;
	};
}