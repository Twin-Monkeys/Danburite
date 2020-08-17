#pragma once

#include <functional>
#include "ContextStateManager.h"

namespace Danburite
{
	class SetupTransaction
	{
	private:
		std::function<void(ObjectGL::ContextStateManager &currentStateMgr)> __setupFunc;

	public:
		void setSetupFunction(
			const std::function<void(ObjectGL::ContextStateManager &currentStateMgr)> &setupFunc) noexcept;

		void setup() const;
	};
}

