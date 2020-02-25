#pragma once

#include "Screen.h"
#include "tstring.h"
#include <unordered_map>
#include "Timer.h"
#include "Win32ScreenException.h"

namespace Danburite
{
	class Win32Screen : public ObjectGL::Screen
	{
	private:
		const HINSTANCE __hInstance;
		tstring __id;
		tstring __windowTitle;

		int __windowWidth;
		int __windowHeight;
		HWND __hWnd = nullptr;

		bool __initialized = false;

		Win32Screen(const Win32Screen &) = delete;
		Win32Screen& operator=(const Win32Screen &) = delete;

		LRESULT __objWndProc(const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept;

		static LRESULT WINAPI __wndProc(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept;
		static Win32Screen *&__getWindow(const HWND hWnd) noexcept;

	public:
		Win32Screen(
			const HINSTANCE hInstance, const std::string_view &id, const std::string_view &title,
			const int windowWidth, const int windowHeight);

		virtual void getClientRect(RECT &rect) const noexcept override;
		virtual void clientToScreen(POINT &clientPoint) const noexcept override;

		void startMainLoop() noexcept;

		virtual int getWidth() const noexcept override;
		virtual int getHeight() const noexcept override;
		virtual HWND getHandler() noexcept override;

		virtual ~Win32Screen() noexcept;
	};
}