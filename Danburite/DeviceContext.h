#pragma once

#include <Windows.h>
#include "DCException.h"
#include <thread>

namespace ObjectGL
{
	class Screen;

	/*
		Window�� �ڽ��� ������ �����常�� ������ �� �ֵ�,
		�� ������κ��� ���� dc�� ������ ���� ������ ������.
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
