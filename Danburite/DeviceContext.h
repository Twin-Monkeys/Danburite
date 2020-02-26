#pragma once

#include <Windows.h>
#include "DCException.h"
#include <thread>

namespace ObjectGL
{
	class Screen;

	/*
		Window는 자신을 생성한 스레드만이 접근할 수 있듯,
		그 윈도우로부터 나온 dc도 동일한 제한 사항을 가진다.
	*/
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
		std::thread::id getOwnerThreadID() const noexcept;

		constexpr operator HDC() const noexcept;

		virtual ~DeviceContext() noexcept;
	};


	constexpr DeviceContext::operator HDC() const noexcept
	{
		return __hDC;
	}
}
