#pragma once

#include "FrameBufferClearFlag.h"

namespace Danburite
{
	class Scene abstract
	{
	protected:
		Scene() = default;

	public:
		virtual void delta(const float deltaTime) noexcept;
		virtual void update() noexcept;
		virtual void draw() noexcept = 0;

		virtual ~Scene() = default;
	};
}