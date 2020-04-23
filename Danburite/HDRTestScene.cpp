#include "HDRTestScene.h"
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

HDRTestScene::HDRTestScene()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::MULTISAMPLE, true);
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	//// Rendering unit 생성 ////

	RenderUnitManager& ruManager = RenderUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	__pBlubRU = AssetImporter::import("res/asset/bulb_fish/scene.gltf");
	Transform &blubTransform = __pBlubRU->getTransform();
	blubTransform.setScale(0.01f);
	blubTransform.setPosition(0.f, 15.f, -35.f);

	__pCargoBayRU = AssetImporter::import("res/asset/cargo_bay/scene.gltf");
	Transform &cargoBayTransform = __pCargoBayRU->getTransform();
	cargoBayTransform.setScale(20.f);


	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 15.f, 50.f);
	cameraTransform.setRotation(-.4f, 0.f, 0.f);

	// Light 초기화

	__pWhiteLight = make_shared<PointLight>();
	__pWhiteLight->setAmbientStrength(.05f);
	__pWhiteLight->setDiffuseStrength(2.f);
	__pWhiteLight->setSpecularStrength(2.f);
	__pWhiteLight->setAttenuation(1.f, 0.027f, 0.0028f);

	__pWhiteLight->setDepthMapSize(2048, 2048);
	__pWhiteLight->setShadowEnabled(true);

	Transform& whiteLightTransform = __pWhiteLight->getTransform();
	whiteLightTransform.setPosition(blubTransform.getPosition() + vec3 { 0.f, .3f, 1.5f });


	//// Deployer / Updater 초기화 ////

	__pLightHandler = make_shared<LightHandler>();
	__pLightHandler->addLight(__pWhiteLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pBlubRU);
	__pUpdater->addUpdatable(__pCargoBayRU);
	__pUpdater->addUpdatable(__pCamera);
	__pUpdater->addUpdatable(__pWhiteLight);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pBlubRU);
	__pDrawer->addDrawable(__pCargoBayRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>();
	__pMsaaPP = make_shared<MSAAPostProcessor>();

	__pPPPipeline = make_shared<PostProcessingPipeline>();
	__pPPPipeline->appendProcessor(__pGammaCorrectionPP);

	Material::setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);
}

bool HDRTestScene::__keyFunc(const float deltaTime) noexcept
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

	CameraTransform& cameraTransform = __pCamera->getTransform();

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

void HDRTestScene::draw() noexcept
{
	__pLightHandler->batchDeploy();
	__pLightHandler->batchBakeDepthMap(*__pDrawer);

	UniformBuffer& ubCamera =
		UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::CAMERA);

	ubCamera.directDeploy(*__pCamera);

	// Render scene onto gamma-corrected frame buffer
	__pPPPipeline->bind();
	GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

	__pDrawer->batchDraw();
	PostProcessingPipeline::unbind();

	// Render to screen
	__pPPPipeline->render();
	RenderContext::getCurrent()->requestBufferSwapping();
}

bool HDRTestScene::delta(const float deltaTime) noexcept
{
	constexpr vec3 pivot { 0.f, 0.f, 0.f };
	constexpr vec3 axis { 0.f, 1.f, 0.f };
	__pBlubRU->getTransform().orbit(deltaTime * .0003f, pivot, axis);
	__pWhiteLight->getTransform().orbit(deltaTime * .0003f, pivot, axis);

	return __keyFunc(deltaTime);
}

void HDRTestScene::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void HDRTestScene::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void HDRTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	__pCamera->setAspectRatio(width, height);
	__pPPPipeline->setScreenSize(width, height);
}

void HDRTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.adjustRotation(-(yDelta * ROTATION_SPEED), -(xDelta * ROTATION_SPEED), 0.f);
}

void HDRTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void HDRTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

bool HDRTestScene::onIdle(const float deltaTime) noexcept
{
	if (!delta(deltaTime))
		return false;

	update();
	return true;
}