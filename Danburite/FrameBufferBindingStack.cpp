#include "FrameBufferBindingStack.h"

using namespace ObjectGL;

namespace Danburite
{
	void FrameBufferBindingStack::push(FrameBuffer &frameBuffer, const bool bindThis) noexcept
	{
		__frameBufferStack.push(&frameBuffer);

		if (!bindThis)
			return;

		frameBuffer.bind();
	}

	void FrameBufferBindingStack::pop(const bool bindPrev) noexcept
	{
		__frameBufferStack.pop();

		if (!bindPrev)
			return;

		if (__frameBufferStack.empty())
			FrameBuffer::unbind();
		else
			__frameBufferStack.top()->bind();
	}

	FrameBuffer *FrameBufferBindingStack::getTop() noexcept
	{
		if (__frameBufferStack.empty())
			return nullptr;

		return __frameBufferStack.top();
	}

	const FrameBuffer *FrameBufferBindingStack::getTop() const noexcept
	{
		if (__frameBufferStack.empty())
			return nullptr;

		return __frameBufferStack.top();
	}
}