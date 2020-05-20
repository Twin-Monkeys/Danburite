#pragma once

namespace Danburite
{
	class Drawable abstract
	{
	public:
		virtual void draw() noexcept = 0;
		virtual void rawDrawcall() noexcept = 0;
	};
}