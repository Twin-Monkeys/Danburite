#include "ShadowTestScene.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderContext.h"
#include "AssetImporter.h"
#include "GLFunctionWrapper.h"
#include "VertexArrayFactory.h"
#include "Constant.h"
#include "PhongMaterial.h"
#include "TextureUtil.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

ShadowTestScene::ShadowTestScene()
{
	// 傈开 可记

	GLFunctionWrapper::setOption(GLOptionType::MULTISAMPLE, true);
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	//// Rendering unit 积己 ////

	__pNanosuitRU = AssetImporter::import("res/asset/nanosuit/scene.gltf");
	Transform &nanosuitTransform = __pNanosuitRU->getTransform();
	nanosuitTransform.setPosition(-10.f, 0.f, 15.f);

	__pSkullRU = AssetImporter::import("res/asset/skull/scene.gltf");
	Transform &skullTransform = __pSkullRU->getTransform();
	skullTransform.setPosition(10.f, 3.f, 15.f);
	skullTransform.setRotation(-quarter_pi<float>(), 0.f, 0.f);
	skullTransform.setScale(5.f);

	__pGoldenSkullRU = AssetImporter::import("res/asset/golden_skull/scene.gltf");
	Transform& goldenSkullTransform = __pGoldenSkullRU->getTransform();
	goldenSkullTransform.setPosition(20.f, 4.f, 10.f);
	goldenSkullTransform.setRotation(0.f, 0.6f, 0.f);
	goldenSkullTransform.setScale(5.f);

	__pRockSurroundRU = AssetImporter::import("res/asset/rock_surround/scene.gltf");
	Transform &rockSurroundTransform = __pRockSurroundRU->getTransform();
	rockSurroundTransform.setPosition(0.f, -82.f, 0.f);
	rockSurroundTransform.setScale(8.f);

	__pChestRU = AssetImporter::import("res/asset/medieval_chest/scene.gltf");
	Transform &chestTransform = __pChestRU->getTransform();
	chestTransform.setPosition(2.f, 4.f, 0.f);
	chestTransform.setRotation(0.f, pi<float>(), 0.f);
	chestTransform.setScale(6.f);

	//// 墨皋扼 积己 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform &cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 5.f, 40.f);

	// Skybox 积己

	const shared_ptr<TextureCubemap>& pSkyboxAlbedoTex =
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

	__pSkybox = make_shared<CubeSkybox>();
	__pSkybox->setAlbedoTexture(pSkyboxAlbedoTex);


	// Light 檬扁拳

	__pBlueLight = make_shared<PointLight>();

	Transform &redLightTransform = __pBlueLight->getTransform();
	redLightTransform.setPosition(20.f, 20.f, 0.f);
	redLightTransform.rotateGlobal(-quarter_pi<float>(), 1.1f, 0.f);

	__pBlueLight->setAlbedo(.1f, .4f, .7f);
	__pBlueLight->setAttenuation(1.f, .007f, .0002f);

	/*
		You can reduce these blocky shadows
		By increasing the depth map resolution or
		By trying to fit the light frustum as closely to the scene as possible.
	*/
	__pBlueLight->setDepthMapSize(2048, 2048);
	__pBlueLight->setShadowEnabled(true);

	__pWhiteLight = make_shared<PointLight>();
	__pWhiteLight->setAttenuation(1.f, .007f, .0002f);

	Transform& whiteLightTransform = __pWhiteLight->getTransform();
	whiteLightTransform.setPosition(-20.f, 20.f, 0.f);
	whiteLightTransform.rotateGlobal(-quarter_pi<float>() * .7f, -.6f, 0.f);

	__pWhiteLight->setDepthMapSize(2048, 2048);
	__pWhiteLight->setShadowEnabled(true);
	//// Deployer / Updater 檬扁拳 ////

	__pLightHandler = make_shared<LightHandler>();
	__pLightHandler->addLight(__pBlueLight);
	__pLightHandler->addLight(__pWhiteLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pCamera);
	__pUpdater->addUpdatable(__pBlueLight);
	__pUpdater->addUpdatable(__pWhiteLight);
	__pUpdater->addUpdatable(__pNanosuitRU);
	__pUpdater->addUpdatable(__pSkullRU);
	__pUpdater->addUpdatable(__pGoldenSkullRU);
	__pUpdater->addUpdatable(__pRockSurroundRU);
	__pUpdater->addUpdatable(__pChestRU);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pNanosuitRU);
	__pDrawer->addDrawable(__pSkullRU);
	__pDrawer->addDrawable(__pGoldenSkullRU);
	__pDrawer->addDrawable(__pRockSurroundRU);
	__pDrawer->addDrawable(__pChestRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>();
	__pMsaaPP = make_shared<MSAAPostProcessor>();

	__pPPPipeline = make_shared<PostProcessingPipeline>();
	// __pPPPipeline->appendProcessor(__pMsaaPP);
	__pPPPipeline->appendProcessor(__pGammaCorrectionPP);

	UniformBufferFactory::getInstance().
		getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL).
		setUniformFloat(ShaderIdentifier::Name::Material::GAMMA, Constant::GammaCorrection::DEFAULT_GAMMA);
}

bool ShadowTestScene::__keyFunc(const float deltaTime) noexcept
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
		LEFT	= (GetAsyncKeyState('A') & 0x8000),
		RIGHT	= (GetAsyncKeyState('D') & 0x8000),
		FRONT	= (GetAsyncKeyState('W') & 0x8000),
		BACK	= (GetAsyncKeyState('S') & 0x8000),
		UP		= (GetAsyncKeyState('E') & 0x8000),
		DOWN	= (GetAsyncKeyState('Q') & 0x8000);

	CameraTransform &cameraTransform = __pCamera->getTransform();

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

	return true;
}

void ShadowTestScene::draw() noexcept
{
	__pLightHandler->batchDeploy();
	__pLightHandler->batchBakeDepthMap(*__pDrawer);

	UniformBuffer &ubCamera =
		UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::CAMERA);

	ubCamera.directDeploy(*__pCamera);

	// Render scene onto gamma-corrected frame buffer
	__pPPPipeline->bind();
	GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

	__pDrawer->batchDraw();
	__pSkybox->draw();
	PostProcessingPipeline::unbind();

	// Render to screen
	__pPPPipeline->render();
	RenderContext::getCurrent()->requestBufferSwapping();
}

bool ShadowTestScene::update(const float deltaTime) noexcept
{
	__pBlueLight->getTransform().orbit(-deltaTime * .0002f, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });
	__pWhiteLight->getTransform().orbit(deltaTime * .0001f, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });

	__pUpdater->update(deltaTime);
	__updated = true;

	return __keyFunc(deltaTime);
}

void ShadowTestScene::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void ShadowTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	__pCamera->setAspectRatio(width, height);
	__pPPPipeline->setScreenSize(width, height);
}

void ShadowTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.rotateFPS(-(yDelta * ROTATION_SPEED), -(xDelta * ROTATION_SPEED));
}

void ShadowTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void ShadowTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

bool ShadowTestScene::onIdle(const float deltaTime) noexcept
{
	return update(deltaTime);
}