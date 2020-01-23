#pragma once

#include <Windows.h>
#include "DCException.h"
#include "AssertException.h"

namespace ObjectGL
{
	class Screen;

	class DeviceContext final
	{
	private:
		Screen &__screen;
		HDC __hDC;

		DeviceContext(const DeviceContext &) = delete;
		DeviceContext& operator=(const DeviceContext &) = delete;

		void __release() noexcept;

	public:
		DeviceContext(Screen &screen);

		void swapBuffers() noexcept;
		void requestScreenClose() noexcept;

		operator HDC() const noexcept;

		virtual ~DeviceContext() noexcept;
	};
}
