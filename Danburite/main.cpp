﻿#include "Win32Screen.h"
#include "DeviceContext.h"
#include "RenderContext.h"
#include "GLFunctionWrapper.h"
#include "RCDSRegisterer.h"
#include "LightTestScene.h"
#include "SpaceScene.h"
#include "ShadowTestScene.h"
#include "NormalMapTestScene.h"

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

	RCDSRegisterer::batchRegister();

	unique_ptr<RenderContext> pRenderContext =
		make_unique<RenderContext>(*pDeviceContext, pixelFormatDesc, attributeDesc);

	pRenderContext->bind();

#ifndef NDEBUG
	GLFunctionWrapper::setOption(GLOptionType::DEBUG_OUTPUT, true);
	GLFunctionWrapper::setOption(GLOptionType::DEBUG_OUTPUT_SYNCHRONOUS, true);

	pRenderContext->setDebugMessageCallback([](
		const GLDebugMessageSourceType source​Type, const GLDebugMessageType messageType​,
		const GLDebugMessageSeverityType severity​Type, const string_view message, GLuint messageID​​) noexcept
	{
		if (severity​Type != GLDebugMessageSeverityType::NOTIFICATION)
		{
			// 버그 잡자!
			int a = 0;
		}
	});
#endif

	GLFunctionWrapper::setVerticalSync(true);

	//// Scene 생성 ////
	shared_ptr<ScreenEventHandler> pScene = make_shared<ShadowTestScene>();

	//// 이벤트 핸들러 등록 ////
	pScreen->setEventHandler(pScene);

	//// 메인 루프 시작 ////
	pScreen->startMainLoop();

	// 리소스 반환
	pScene.reset();
	pRenderContext.reset();
	pDeviceContext.reset();
	pScreen.reset();

	return 0;
}