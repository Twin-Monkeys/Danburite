#pragma once

#include <Windows.h>
#include <memory>
#include "PixelFormatDescriptor.h"
#include "RCAttributeDescriptor.h"
#include "ScreenEventHandler.h"
#include <thread>

namespace ObjectGL
{
	class Screen abstract
	{
	private:
		std::weak_ptr<ScreenEventHandler> __pEventHandler;
		const std::thread::id __ownerThreadID;

	public:
		Screen() noexcept;

		std::shared_ptr<ScreenEventHandler> getEventHandler() const noexcept;
		void setEventHandler(const std::weak_ptr<ScreenEventHandler> &pEventHandler) noexcept;

		void show() noexcept;

		virtual void getClientRect(RECT &rect) const noexcept = 0;
		virtual void clientToScreen(POINT &clientPoint) const noexcept = 0;

		virtual int getWidth() const noexcept = 0;
		virtual int getHeight() const noexcept = 0;

		void invalidate() noexcept;
		void validate() noexcept;

		std::thread::id getOwnerThreadID() const noexcept;

		virtual HWND getHandler() noexcept = 0;

		operator HWND() noexcept;

		virtual ~Screen() = default;
	};
}
