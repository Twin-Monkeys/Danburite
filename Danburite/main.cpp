#include "Win32Screen.h"
#include "DeviceContext.h"
#include "RenderContext.h"
#include "GLFunctionWrapper.h"
#include "RCDSRegisterer.h"
#include "BlinnPhongTestScene.h"
#include "LightTestScene.h"
#include "SpaceScene.h"
#include "ShadowTestScene.h"

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

	RCDSRegisterer::batchRegister();

	unique_ptr<RenderContext> pRenderContext =
		make_unique<RenderContext>(*pDeviceContext, pixelFormatDesc, attributeDesc);

	pRenderContext->bind();
	GLFunctionWrapper::setVerticalSync(true);

	//// Scene ���� ////
	shared_ptr<ScreenEventHandler> pScene = make_shared<LightTestScene>();

	//// �̺�Ʈ �ڵ鷯 ��� ////
	pScreen->setEventHandler(pScene);

	//// ���� ���� ���� ////
	pScreen->startMainLoop();

	// ���ҽ� ��ȯ
	pScene.reset();
	pRenderContext.reset();
	pDeviceContext.reset();
	pScreen.reset();

	return 0;
}