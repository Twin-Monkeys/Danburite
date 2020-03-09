#include "Drawer.h"

using namespace std;

namespace Danburite
{
	void Drawer::addDrawable(const weak_ptr<Drawable> &pDrawable) noexcept
	{
		__drawables.add(pDrawable);
	}

	void Drawer::batchDraw() noexcept
	{
		__drawables.safeTraverse(&Drawable::draw);
	}

	void Drawer::batchRawDrawCall() noexcept
	{
		__drawables.safeTraverse(&Drawable::rawDrawCall);
	}
}