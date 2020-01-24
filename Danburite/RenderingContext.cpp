#include "RenderingContext.h"
#include "DeviceContext.h"
#include <algorithm>

using namespace std;
using namespace ObjectGL;

namespace ObjectGL
{
	HGLRC RenderingContext::__createRC(
		DeviceContext &deviceContext,
		const PixelFormatDescriptor &pixelFormatDesc, const RCAttributeDescriptor &desc)
	{
		__setPixelFormat(deviceContext, pixelFormatDesc);
		__validate(deviceContext);

		const HGLRC retVal = wglCreateContextAttribsARB(deviceContext, nullptr, desc);
		if (!retVal)
			throw RCException("Cannot create rendering context");

		return retVal;
	}

	RenderingContext::RenderingContext(
		DeviceContext &deviceContext,
		const PixelFormatDescriptor &pixelFormatDesc, const RCAttributeDescriptor &desc) :
		BindableObject(__createRC(deviceContext, pixelFormatDesc, desc)), __deviceContext(deviceContext)
	{}

	void RenderingContext::__validate(DeviceContext &deviceContext)
	{
		if (__glInitialized)
			return;

		const HGLRC hTmpRC = wglCreateContext(deviceContext);
		if (!hTmpRC)
			throw RCException("Cannot initialize the device");

		wglMakeCurrent(deviceContext, hTmpRC);

		if (glewInit() != GLEW_OK)
			throw RCException("Cannot initialize the device");

		wglMakeCurrent(deviceContext, nullptr);
		wglDeleteContext(hTmpRC);

		__glInitialized = true;
	}

	void RenderingContext::__setPixelFormat(const HDC hDC, const PIXELFORMATDESCRIPTOR &descRaw)
	{
		/*
			Warning:

			Unfortunately, Windows does not allow the user to change the pixel format of a window.
			(Setting the pixel format on the same hWnd twice is not allowed)
			You get to set it exactly once. Therefore, if you want to use a different pixel format
			from the one your fake context used (for sRGB or multisample framebuffers,
			or just different bit-depths of buffers), you must destroy the window entirely and
			recreate it after we are finished with the dummy context.
		*/
		const int FORMAT = ChoosePixelFormat(hDC, &descRaw);

		if (!FORMAT)
			throw RCException("Cannot retrieve the pixel format");

		if (!SetPixelFormat(hDC, FORMAT, &descRaw))
			throw RCException("Cannot deploy the pixel format");
	}

	void RenderingContext::__release() noexcept
	{
		wglDeleteContext(ID);
	}

	void RenderingContext::_onBind() noexcept
	{
		wglMakeCurrent(__deviceContext, ID);
		__pCurrent = this;
	}

	RenderingContext::~RenderingContext() noexcept
	{
		__release();
	}

	void RenderingContext::requestBufferSwapping() noexcept
	{
		__pCurrent->__deviceContext.swapBuffers();
	}

	void RenderingContext::requestScreenClose() noexcept
	{
		__pCurrent->__deviceContext.requestScreenClose();
	}

	void RenderingContext::unbind() noexcept
	{
		if (!__pCurrent)
			return;

		wglMakeCurrent(__pCurrent->__deviceContext, nullptr);
		__pCurrent = nullptr;
		_unbind();
	}
}