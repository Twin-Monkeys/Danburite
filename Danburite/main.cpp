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
	//// Window �ʱ�ȭ ////
	unique_ptr<Win32Screen> pScreen =
		make_unique<Win32Screen>(hInstance, "screen", "Danburite", 1600, 900);

	//// ���ؽ�Ʈ ���� ////
	unique_ptr<DeviceContext> pDeviceContext = make_unique<DeviceContext>(*pScreen);

	const PixelFormatDescriptor pixelFormatDesc {};
	const RCAttributeDescriptor attributeDesc {};

	unique_ptr<RenderingContext> pRenderingContext =
		make_unique<RenderingContext>(*pDeviceContext, pixelFormatDesc, attributeDesc);

	pRenderingContext->bind();
	GLFunctionWrapper::setVerticalSync(false);

	//// Scene ���� ////
	shared_ptr<ScreenEventHandler> pScene = make_shared<DemoScene4>();

	//// �̺�Ʈ �ڵ鷯 ��� ////
	pScreen->setEventHandler(pScene);

	//// ���� ���� ���� ////
	pScreen->startMainLoop();

	// ���ҽ� ��ȯ
	pScene.reset();
	pRenderingContext.reset();
	pDeviceContext.reset();
	pScreen.reset();

	return 0;
}