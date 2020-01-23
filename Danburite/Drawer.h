#pragma once

#include "Drawable.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class Drawer
	{
	private:
		ObjectGL::WeakPointerContainer<Drawable> __drawables;

	public:
		void addDrawable(const std::weak_ptr<Drawable> &pDrawable) noexcept;
		void batchDraw() noexcept;
	};
}
