#pragma once

#include <unordered_set>
#include "Drawable.h"

namespace Danburite
{
	class Drawer
	{
	private:
		std::unordered_set<Drawable *> __drawableSet;

	public:
		void addDrawable(Drawable &drawable) noexcept;
		void removeDrawable(Drawable &drawable) noexcept;

		void batchDraw() noexcept;
		void batchRawDrawcall() noexcept;
	};
}
