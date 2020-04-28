#pragma once

namespace Danburite
{
	class Updatable abstract
	{
	public:
		virtual void update(const float deltaTime) noexcept = 0;
		virtual ~Updatable() = default;
	};
}
