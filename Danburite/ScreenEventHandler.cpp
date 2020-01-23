#include "ScreenEventHandler.h"

namespace ObjectGL
{
	void ScreenEventHandler::onDisplay() noexcept {}
	void ScreenEventHandler::onResize(const int width, const int height) noexcept {}
	void ScreenEventHandler::onMouseDelta(const int xDelta, const int yDelta) noexcept {}
	void ScreenEventHandler::onMouseMButtonDown(const int x, const int y) noexcept {}
	void ScreenEventHandler::onMouseWheel(const short zDelta) noexcept {}
	void ScreenEventHandler::onIdle(const float deltaTime) noexcept {}
}