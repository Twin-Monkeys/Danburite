#include "DeviceContext.h"
#include "Screen.h"
#include "RenderContext.h"

using namespace std;

namespace ObjectGL
{
	DeviceContext::DeviceContext(Screen &screen) :
		__screen(screen)
	{
		if (__screen.getOwnerThreadID() != this_thread::get_id())
			throw DCException("Current thread is not identical with owner thread of the screen");

		__hDC = GetDC(screen);

		if (!__hDC)
			throw DCException("Cannot create device context");
	}

	void DeviceContext::__release() noexcept
	{
		const int result = ReleaseDC(__screen, __hDC);
		assert(result);
	}

	void DeviceContext::swapBuffers() noexcept
	{
		const BOOL result = SwapBuffers(__hDC);
		assert(result);
	}

	thread::id DeviceContext::getOwnerThreadID() const noexcept
	{
		return __screen.getOwnerThreadID();
	}

	DeviceContext::~DeviceContext() noexcept
	{
		__release();
	}
}