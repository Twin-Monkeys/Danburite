#pragma once

#include "RenderContext.h"
#include <stack>
#include "FrameBuffer.h"

namespace Danburite
{
	class FrameBufferBindingStack : public ObjectGL::ContextDependentSingleton<FrameBufferBindingStack>
	{
		friend ObjectGL::ContextDependentSingleton<FrameBufferBindingStack>;

	private:
		std::stack<ObjectGL::FrameBuffer *> __frameBufferStack;
		FrameBufferBindingStack() = default;

	public:
		void push(ObjectGL::FrameBuffer &frameBuffer, const bool bindThis = true) noexcept;
		void pop(const bool bindPrev = true) noexcept;

		ObjectGL::FrameBuffer *getTop() noexcept;
		const ObjectGL::FrameBuffer *getTop() const noexcept;
	};
}