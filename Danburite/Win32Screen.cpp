#include "Win32Screen.h"
#include <atlstr.h>
#include <Windowsx.h>
#include <cassert>

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Win32Screen::Win32Screen(
		const HINSTANCE hInstance, const string_view &id, const string_view &title,
		const int windowWidth, const int windowHeight) :
		__hInstance(hInstance), __id(CA2CT(id.data())), __windowTitle(CA2CT(title.data())),
		__windowWidth(windowWidth), __windowHeight(windowHeight)
	{
		WNDCLASSEX wndClass = {};

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = (CS_VREDRAW | CS_HREDRAW);
		wndClass.lpfnWndProc = __wndProc;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
		wndClass.lpszClassName = __id.c_str();
		wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		RegisterClassEx(&wndClass);

		DWORD winStyleFlag = WS_OVERLAPPEDWINDOW;
		winStyleFlag &= (~WS_THICKFRAME);
		winStyleFlag &= (~WS_MAXIMIZEBOX);

		RECT newRect;
		BOOL valid = SetRect(&newRect, 0, 0, windowWidth, windowHeight);
		assert(valid);

		valid = AdjustWindowRect(&newRect, winStyleFlag, false);
		assert(valid);

		__hWnd = CreateWindow(
			__id.c_str(), __windowTitle.c_str(),
			winStyleFlag,

			// Left, Top
			10, 10,

			// Width
			(newRect.right - newRect.left),

			// Height
			(newRect.bottom - newRect.top),
			nullptr, nullptr, hInstance, nullptr);

		if (!__hWnd)
			throw Win32ScreenException("Cannot create window");

		__getWindow(__hWnd) = this;
	}

	LRESULT Win32Screen::__objWndProc(const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (msg == WM_DESTROY)
		{
			const BOOL result = ClipCursor(nullptr);
			assert(result);

			PostQuitMessage(EXIT_SUCCESS);
			return 0;
		}

		const shared_ptr<ScreenEventHandler> &pEventHandler = getEventHandler();
		if (!pEventHandler)
		{
			const BOOL valid = DestroyWindow(__hWnd);
			assert(valid);

			return 0;
		}

		switch (msg)
		{
		case WM_SIZE:
		{
			RECT rect;
			getClientRect(rect);

			const int WIDTH = (rect.right - rect.left);
			const int HEIGHT = (rect.bottom - rect.top);

			POINT windowCenter = { WIDTH / 2, HEIGHT / 2 };
			clientToScreen(windowCenter);

			BOOL valid = SetCursorPos(windowCenter.x, windowCenter.y);
			assert(valid);

			POINT leftTop = {};
			POINT rightBottom = { WIDTH, HEIGHT };
			clientToScreen(leftTop);
			clientToScreen(rightBottom);

			rect = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
			valid = ClipCursor(&rect);
			assert(valid);

			__windowWidth = WIDTH;
			__windowHeight = HEIGHT;

			pEventHandler->onResize(WIDTH, HEIGHT);

			if (!__initialized)
			{
				__initialized = true;
				invalidate();
			}
		}
			break;

		case WM_PAINT:
			if (!__initialized)
				break;

			pEventHandler->onDisplay();
			validate();
			break;

		case WM_MOUSEMOVE:
		{
			const int X = GET_X_LPARAM(lParam);
			const int Y = GET_Y_LPARAM(lParam);
			const SIZE WIN_SIZE_HALF = { getWidth() / 2, getHeight() / 2 };

			const LONG X_DELTA = (WIN_SIZE_HALF.cx - X);
			const LONG Y_DELTA = (WIN_SIZE_HALF.cy - Y);

			if (!X_DELTA && !Y_DELTA)
				break;

			POINT windowCenter = { WIN_SIZE_HALF.cx, WIN_SIZE_HALF.cy };
			clientToScreen(windowCenter);

			const BOOL valid = SetCursorPos(windowCenter.x, windowCenter.y);
			assert(valid);

			pEventHandler->onMouseDelta(X_DELTA, Y_DELTA);
		}
			break;

		case WM_MBUTTONDOWN:
			pEventHandler->onMouseMButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;

		case WM_MOUSEWHEEL:
			pEventHandler->onMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
			break;

		case WM_SETCURSOR:
			if (LOWORD(lParam) == HTCLIENT)
				SetCursor(nullptr);
			else
			{
				const BOOL valid = ClipCursor(nullptr);
				assert(valid);
			}
			break;

		default:
			return DefWindowProc(__hWnd, msg, wParam, lParam);
		}

		return 0;
	}

	LRESULT Win32Screen::__wndProc(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		Win32Screen *const pScreen = __getWindow(hWnd);

		if (pScreen)
			return pScreen->__objWndProc(msg, wParam, lParam);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	Win32Screen *&Win32Screen::__getWindow(const HWND hWnd) noexcept
	{
		static unordered_map<HWND, Win32Screen *> windowMap;
		
		return windowMap[hWnd];
	}

	void Win32Screen::getClientRect(RECT &rect) const noexcept
	{
		const BOOL valid = GetClientRect(__hWnd, &rect);
		assert(valid);
	}

	void Win32Screen::clientToScreen(POINT &clientPoint) const noexcept
	{
		const BOOL valid = ClientToScreen(__hWnd, &clientPoint);
		assert(valid);
	}

	/*
		주의: 메인 루프는 스레드 당 하나만 활성화되어야 합니다.
		즉, 윈도우마다 별도의 스레드가 필요합니다.
	*/
	void Win32Screen::startMainLoop() noexcept
	{
		const shared_ptr<ScreenEventHandler> &pEventHandler = getEventHandler();
		if (!pEventHandler)
			return;

		show();

		MSG msg;
		float accumTime = 0.f;
		int count = 0;

		Timer<> timer;
		do
		{
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				const BOOL valid = TranslateMessage(&msg);
				assert(valid);

				DispatchMessage(&msg);
			}
			else
			{
				float deltaTime = 0.f;

				if (timer.end())
				{
					deltaTime = timer.getElapsedTime();
					accumTime += deltaTime;
					count++;
				}
				timer.start();

				if (accumTime > 1000.f)
				{
					const float avgTime = (accumTime / float(count));

					static TCHAR postfix[512];
					_stprintf_s(postfix, _T(" [delta: %.1fms / fps: %.1f]"), avgTime, 1000.f / avgTime);

					SetWindowText(__hWnd, (__windowTitle + postfix).c_str());

					accumTime = 0.f;
					count = 0;
				}

				pEventHandler->onIdle(deltaTime);
				invalidate();
			}
		}
		while (msg.message != WM_QUIT);
	}

	int Win32Screen::getWidth() const noexcept
	{
		return __windowWidth;
	}

	int Win32Screen::getHeight() const noexcept
	{
		return __windowHeight;
	}

	HWND Win32Screen::getHandler() noexcept
	{
		return __hWnd;
	}

	Win32Screen::~Win32Screen() noexcept
	{
		__getWindow(__hWnd) = nullptr;

		const BOOL valid = UnregisterClass(__id.c_str(), __hInstance);
		assert(valid);
	}

	shared_ptr<Win32Screen> Win32Screen::createDummy(const HINSTANCE hInstance)
	{
		return make_shared<Win32Screen>(hInstance, "dummy", "dummy", 1, 1);
	}
};