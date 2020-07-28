#include "Drawer.h"

using namespace std;

namespace Danburite
{
	void Drawer::addDrawable(Drawable &drawable) noexcept
	{
		__drawableSet.emplace(&drawable);
	}

	void Drawer::removeDrawable(Drawable &drawable) noexcept
	{
		__drawableSet.erase(&drawable);
	}

	void Drawer::batchDraw() noexcept
	{
		for (Drawable *const pDrawable : __drawableSet)
			pDrawable->draw();
	}

	void Drawer::batchRawDrawcall() noexcept
	{
		for (Drawable *const pDrawable : __drawableSet)
			pDrawable->rawDrawcall();
	}
}