#include "LightingTestScene.h"
#include "VertexAttributeListFactory.h"
#include "RenderContext.h"
#include "AssetImporter.h"
#include "GLFunctionWrapper.h"
#include "VertexArrayFactory.h"
#include "Constant.h"
#include "PhongMaterial.h"
#include "TextureUtil.h"
#include "UniformBufferFactory.h"
#include <glm/gtx/rotate_vector.hpp>
#include "ForwardRenderingPipeline.h"
#include "LightPrePassRenderingPipeline.h"
#include "GammaCorrectionPostProcessor.h"
#include "BloomPostProcessor.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

LightingTestScene::LightingTestScene()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::MULTISAMPLE, true);
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	//// Rendering unit 생성 ////

	__pCorridorObj = AssetImporter::import("res/asset/corridor/scene.gltf");


	//// 카메라 초기화 ////

	Transform &cameraTransform = __camera.getTransform();
	cameraTransform.setPosition(0.f, 15.f, 50.f);
	cameraTransform.setRotation(-0.4f, 0.f, 0.f);


	// Light 초기화

	__pBlueLight = &__lightMgr.createLight<PointLight>();
	__pBlueLight->setAlbedo(.2f, .3f, 1.f);
	__pBlueLight->setAmbientStrength(.05f);
	__pBlueLight->setDiffuseStrength(1.f);
	__pBlueLight->setSpecularStrength(1.f);
	__pBlueLight->setAttenuation(1.f, 0.09f, 0.032f);
	__pBlueLight->setShadowEnabled(true);

	Transform& blueLightTransform = __pBlueLight->getTransform();
	blueLightTransform.setPosition({ 0.f, .3f, 3.5f });

	__pRedLight = &__lightMgr.createLight<PointLight>();
	__pRedLight->setAlbedo(1.f, .1f, .1f);
	__pRedLight->setAmbientStrength(.05f);
	__pRedLight->setDiffuseStrength(2.f);
	__pRedLight->setSpecularStrength(2.f);
	__pRedLight->setAttenuation(1.f, 0.22f, 0.20f);
	__pRedLight->setShadowEnabled(true);

	Transform &redLightTransform = __pRedLight->getTransform();
	redLightTransform.setPosition(vec3{ -2.f, .3f, -2.f });


	//// Updater / Drawer 초기화 ////

	__updater.add(__camera);
	__updater.add(*__pBlueLight);
	__updater.add(*__pRedLight);
	__updater.add(*__pCorridorObj);

	__drawer.add(*__pCorridorObj);


	// Skybox

	/*const shared_ptr<TextureCubemap> &pSkyboxAlbedoTex =
		TextureUtil::createTextureCubemapFromImage(
			{
				"res/image/skybox/space/right.png",
				"res/image/skybox/space/left.png",
				"res/image/skybox/space/top.png",
				"res/image/skybox/space/bot.png",
				"res/image/skybox/space/front.png",
				"res/image/skybox/space/back.png"
			});

	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_R, TextureWrapValue::CLAMP_TO_EDGE);

	__skybox.setAlbedoTexture(pSkyboxAlbedoTex);
	__skybox.setLuminance(.1f);
	__skybox.setEnabled(true);*/

	Material::setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);

	// __pPPPipeline->appendProcessor<MSAAPostProcessor>(true);
	__ppPipeline.appendProcessor<GammaCorrectionPostProcessor>(true);
	__ppPipeline.appendProcessor<BloomPostProcessor>();
	__pHDRPP = &__ppPipeline.appendProcessor<HDRPostProcessor>();

	__pRenderingPipeline = make_unique<LightPrePassRenderingPipeline>(
		__lightMgr, __camera, __drawer, __skybox, __ppPipeline);

	/*__pRenderingPipeline = make_unique<ForwardRenderingPipeline>(
		__lightMgr, *__pCamera, __drawer, __skybox, __ppPipeline);*/
}

bool LightingTestScene::__keyFunc(const float deltaTime) noexcept
{
	const bool ESC = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
	if (ESC)
		return false;

	float accel = 1.f;
	const bool SHIFT = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
	if (SHIFT)
		accel *= 4.f;

	constexpr float MOVE_SPEED_FACTOR = .013f;
	const float MOVE_SPEED = (MOVE_SPEED_FACTOR * deltaTime * accel);

	const bool
		LEFT = (GetAsyncKeyState('A') & 0x8000),
		RIGHT = (GetAsyncKeyState('D') & 0x8000),
		FRONT = (GetAsyncKeyState('W') & 0x8000),
		BACK = (GetAsyncKeyState('S') & 0x8000),
		UP = (GetAsyncKeyState('E') & 0x8000),
		DOWN = (GetAsyncKeyState('Q') & 0x8000);

	Transform& cameraTransform = __camera.getTransform();

	if (LEFT)
		cameraTransform.moveHorizontal(-MOVE_SPEED);

	if (RIGHT)
		cameraTransform.moveHorizontal(MOVE_SPEED);

	if (FRONT)
		cameraTransform.moveForward(-MOVE_SPEED);

	if (BACK)
		cameraTransform.moveForward(MOVE_SPEED);

	if (UP)
		cameraTransform.moveVertical(MOVE_SPEED);

	if (DOWN)
		cameraTransform.moveVertical(-MOVE_SPEED);

	const bool
		KEY1 = (GetAsyncKeyState('1') & 0x8000),
		KEY2 = (GetAsyncKeyState('2') & 0x8000);

	if (KEY1)
		__pHDRPP->setExposure(__pHDRPP->getExposure() - .1f);

	if (KEY2)
		__pHDRPP->setExposure(__pHDRPP->getExposure() + .1f);

	return true;
}

void LightingTestScene::draw() noexcept
{
	__pRenderingPipeline->render();
	RenderContext::getCurrent()->requestBufferSwapping();
}

bool LightingTestScene::update(const float deltaTime) noexcept
{
	constexpr vec3 pivot { 0.f, 0.f, 0.f };
	constexpr vec3 axis { 0.f, 1.f, 0.f };

	__updater.process(&Updatable::update, deltaTime);
	__updated = true;

	return __keyFunc(deltaTime);
}

void LightingTestScene::onDisplay() noexcept
{
	if (!__updated)
		return;
	
	draw();
}

void LightingTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	__pRenderingPipeline->setScreenSize(width, height);
}

void LightingTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform &cameraTransform = __camera.getTransform();
	cameraTransform.rotateFPS(-(yDelta * ROTATION_SPEED), -(xDelta * ROTATION_SPEED));
}

void LightingTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__camera.resetFov();
}

void LightingTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__camera.adjustFov(ZOOM_SPEED * zDelta);
}

bool LightingTestScene::onIdle(const float deltaTime) noexcept
{
	return update(deltaTime);
}