#pragma once

namespace Danburite
{
	class Updatable abstract
	{
	public:
		virtual void update() noexcept = 0;
		virtual ~Updatable() = default;
	};
}
