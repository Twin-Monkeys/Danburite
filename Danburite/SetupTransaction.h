#pragma once

#include <functional>
#include "RenderContext.h"

namespace Danburite
{
	class SetupTransaction
	{
	private:
		ObjectGL::ContextStateManager &__stateMgr =
			ObjectGL::RenderContext::getCurrentStateManager();

		std::function<void(ObjectGL::ContextStateManager &currentStateMgr)> __setupFunc;

	public:
		void setup(const std::function<void(ObjectGL::ContextStateManager &currentStateMgr)> &setupFunc) noexcept;
		void operator()() const;
	};
}

