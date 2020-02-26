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
		if (deviceContext.getOwnerThreadID() != this_thread::get_id())
			throw RCException("Current thread is not identical with owner thread of the device context");

		__setPixelFormat(deviceContext, pixelFormatDesc);
		__validate(deviceContext);

		const HGLRC retVal = wglCreateContextAttribsARB(deviceContext, nullptr, desc);
		if (!retVal)
			throw RCException("Cannot create rendering context");

		return retVal;
	}

	/*
		RenderContext는 하나의 dc에 대해 하나만 바인드 (make current) 할 수 있다.
	*/
	RenderContext::RenderContext(
		DeviceContext &deviceContext,
		const PixelFormatDescriptor &pixelFormatDesc, const RCAttributeDescriptor &desc) :
		BindableObject(__createRC(deviceContext, pixelFormatDesc, desc)), __deviceContext(deviceContext)
	{
		const RenderContext *const pPrevContext = getCurrent();

		BOOL result = wglMakeCurrent(deviceContext, ID);
		assert(result);

		GLint numExtensions = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
		assert(glGetError() == GL_NO_ERROR);

		for (GLint i = 0; i < numExtensions; i++)
		{
			__extensionMap.emplace(reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)));
			assert(glGetError() == GL_NO_ERROR);
		}

		if (pPrevContext)
			result = wglMakeCurrent(deviceContext, pPrevContext->ID);
		else
			result = wglMakeCurrent(deviceContext, nullptr);

		assert(result);
		
		for (const auto &onCreateListener : __getOnCreateListenerContainer())
			onCreateListener(this);
	}

	void RenderContext::__release() noexcept
	{
		// 현재 스레드 상에서, DC와 바인딩 되어 있는 RC가 this인 경우
		if (this == getCurrent())
			unbind();

		const BOOL result = wglDeleteContext(ID);
		assert(result);
	}

	void RenderContext::__validate(DeviceContext &deviceContext)
	{
		static unordered_map<thread::id, bool> initializedThreads;

		// TODO: Checking thread safety
		bool &initialized = initializedThreads[this_thread::get_id()];
		if (initialized)
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

		initialized = true;
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

	unordered_set<void(*)(const RenderContext *)> &
		RenderContext::__getOnCreateListenerContainer() noexcept
	{
		static unordered_set<void(*)(const RenderContext *)> onCreateListenerContainer;
		return onCreateListenerContainer;
	}

	unordered_set<void(*)(const RenderContext *)> &
		RenderContext::__getOnDestroyListenerContainer() noexcept
	{
		static unordered_set<void(*)(const RenderContext *)> onDestroyListenerContainer;
		return onDestroyListenerContainer;
	}

	unordered_map<thread::id, RenderContext *> &RenderContext::__getCurrentMap() noexcept
	{
		static unordered_map<thread::id, RenderContext *> rcMap;
		return rcMap;
	}

	RenderContext *&RenderContext::__getCurrentSlot() noexcept
	{
		return __getCurrentMap()[this_thread::get_id()];
	}

	void RenderContext::_onBind() noexcept
	{
		const BOOL result = wglMakeCurrent(__deviceContext, ID);
		assert(result);

		__getCurrentSlot() = this;
	}

	RenderContext::~RenderContext() noexcept
	{
		for (const auto &onDestroyListener : __getOnDestroyListenerContainer())
			onDestroyListener(this);

		__release();
	}

	void RenderContext::requestBufferSwapping() noexcept
	{
		__deviceContext.swapBuffers();
	}

	bool RenderContext::isSupportedExtension(const string &extensionName) const noexcept
	{
		return __extensionMap.count(extensionName);
	}

	void RenderContext::unbind() noexcept
	{
		RenderContext *&pCurrent = __getCurrentSlot();
		if (!pCurrent)
			return;

		const bool valid = wglMakeCurrent(pCurrent->__deviceContext, nullptr);
		assert(valid);

		pCurrent = nullptr;
		_unbind();
	}

	RenderContext *RenderContext::getCurrent() noexcept
	{
		return __getCurrentSlot();
	}
}