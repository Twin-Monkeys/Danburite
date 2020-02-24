#include "RenderContext.h"
#include "DeviceContext.h"
#include <algorithm>
#include <cassert>

using namespace std;
using namespace ObjectGL;

namespace ObjectGL
{
	HGLRC RenderContext::__createRC(
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

	RenderContext::RenderContext(
		DeviceContext &deviceContext,
		const PixelFormatDescriptor &pixelFormatDesc, const RCAttributeDescriptor &desc) :
		BindableObject(__createRC(deviceContext, pixelFormatDesc, desc)), __deviceContext(deviceContext)
	{
		for (const auto &onCreateListener : __onCreateListeners)
			onCreateListener(this);
	}

	void RenderContext::__validate(DeviceContext &deviceContext)
	{
		if (__glInitialized)
			return;

		const HGLRC hTmpRC = wglCreateContext(deviceContext);
		if (!hTmpRC)
			throw RCException("Cannot initialize the device");

		BOOL result = wglMakeCurrent(deviceContext, hTmpRC);
		assert(result);

		if (glewInit() != GLEW_OK)
			throw RCException("Cannot initialize the device");

		result = wglMakeCurrent(deviceContext, nullptr);
		assert(result);

		result = wglDeleteContext(hTmpRC);
		assert(result);

		__glInitialized = true;
	}

	void RenderContext::__setPixelFormat(const HDC hDC, const PIXELFORMATDESCRIPTOR &descRaw)
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

	void RenderContext::__release() noexcept
	{
		const BOOL result = wglDeleteContext(ID);
		assert(result);
	}

	void RenderContext::_onBind() noexcept
	{
		const BOOL result = wglMakeCurrent(__deviceContext, ID);
		assert(result);

		__pCurrent = this;
	}

	RenderContext::~RenderContext() noexcept
	{
		__release();

		for (const auto &onDestroyListener : __onDestroyListeners)
			onDestroyListener(this);
	}

	void RenderContext::requestBufferSwapping() noexcept
	{
		__pCurrent->__deviceContext.swapBuffers();
	}

	void RenderContext::requestScreenClose() noexcept
	{
		__pCurrent->__deviceContext.requestScreenClose();
	}

	void RenderContext::unbind() noexcept
	{
		if (!__pCurrent)
			return;

		const BOOL result = wglMakeCurrent(__pCurrent->__deviceContext, nullptr);
		assert(result);

		__pCurrent = nullptr;
		_unbind();
	}
}