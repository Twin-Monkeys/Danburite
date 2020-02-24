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
		const int result = ReleaseDC(__screen, __hDC);
		assert(result);
	}

	void DeviceContext::swapBuffers() noexcept
	{
		const BOOL result = SwapBuffers(__hDC);
		assert(result);
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