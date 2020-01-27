#include "Win32Screen.h"
#include "DeviceContext.h"
#include "RenderingContext.h"
#include "DemoScene4.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace Danburite;
using namespace ObjectGL;

int APIENTRY _tWinMain(const HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	//// Window 초기화 ////
	unique_ptr<Win32Screen> pScreen =
		make_unique<Win32Screen>(hInstance, "screen", "Danburite", 1600, 900);

	//// 컨텍스트 설정 ////
	unique_ptr<DeviceContext> pDeviceContext = make_unique<DeviceContext>(*pScreen);

	const PixelFormatDescriptor pixelFormatDesc {};
	const RCAttributeDescriptor attributeDesc {};

	unique_ptr<RenderingContext> pRenderingContext =
		make_unique<RenderingContext>(*pDeviceContext, pixelFormatDesc, attributeDesc);

	pRenderingContext->bind();
	GLFunctionWrapper::setVerticalSync(false);

	//// Scene 생성 ////
	shared_ptr<ScreenEventHandler> pScene = make_shared<DemoScene4>();

	//// 이벤트 핸들러 등록 ////
	pScreen->setEventHandler(pScene);

	//// 메인 루프 시작 ////
	pScreen->startMainLoop();

	// 리소스 반환
	pScene.reset();
	pRenderingContext.reset();
	pDeviceContext.reset();
	pScreen.reset();

	return 0;
}