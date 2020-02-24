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
		/*
			ShowWindow shows (or hides) a window in a certain manner.
			For example, the function can minimize, maximize, or restore a given window.
			
			The function returns 0 if the window had been hidden before the call,
			Or a non-zero value if it had been visible.
		*/
		ShowWindow(*this, SW_SHOWDEFAULT);

		const BOOL result = UpdateWindow(*this);
		assert(result);
	}

	void Screen::close() noexcept
	{
		const BOOL result = DestroyWindow(*this);
		assert(result);
	}

	void Screen::invalidate() noexcept
	{
		const BOOL result = InvalidateRect(*this, nullptr, false);
		assert(result);
	}

	void Screen::validate() noexcept
	{
		const BOOL result = ValidateRect(*this, nullptr);
		assert(result);
	}

	Screen::operator HWND() noexcept
	{
		return getHandler();
	}
}