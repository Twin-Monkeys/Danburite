#include "Screen.h"
#include "DeviceContext.h"
#include "RenderContext.h"

using namespace std;

namespace ObjectGL
{
	shared_ptr<ScreenEventHandler> Screen::getEventHandler() const noexcept
	{
		return __pEventHandler.lock();
	}

	void Screen::setEventHandler(const weak_ptr<ScreenEventHandler> &pEventHandler) noexcept
	{
		__pEventHandler = pEventHandler;
	}

	void Screen::show() noexcept
	{
		ShowWindow(*this, SW_SHOWDEFAULT);
		UpdateWindow(*this);
	}

	void Screen::close() noexcept
	{
		DestroyWindow(*this);
	}

	void Screen::invalidate() noexcept
	{
		InvalidateRect(*this, nullptr, false);
	}

	void Screen::validate() noexcept
	{
		ValidateRect(*this, nullptr);
	}

	Screen::operator HWND() noexcept
	{
		return getHandler();
	}
}