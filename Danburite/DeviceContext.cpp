#include "DeviceContext.h"
#include "Screen.h"
#include "RenderContext.h"

using namespace std;

namespace ObjectGL
{
	DeviceContext::DeviceContext(Screen &screen) :
		__screen(screen)
	{
		__hDC = GetDC(screen);

		if (!__hDC)
			throw DCException("Cannot create device context");
	}

	void DeviceContext::__release() noexcept
	{
		ReleaseDC(__screen, __hDC);
	}

	void DeviceContext::swapBuffers() noexcept
	{
		SwapBuffers(__hDC);
	}

	void DeviceContext::requestScreenClose() noexcept
	{
		__screen.close();
	}

	DeviceContext::operator HDC() const noexcept
	{
		return __hDC;
	}

	DeviceContext::~DeviceContext() noexcept
	{
		__release();
	}
}