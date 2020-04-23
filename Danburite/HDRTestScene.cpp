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
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, false);


	//// Rendering unit 생성 ////

	RenderUnitManager& ruManager = RenderUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<Texture2D>& pFloor_diffuse =
		TextureUtil::createTexture2DFromImage("res/image/metal.jpg");

	pFloor_diffuse->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pFloor_diffuse->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pFloor_diffuse->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pFloor_diffuse->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<VertexArray>& pFloorVA =
		vaFactory.getVertexArrayPtr(ShapeType::RECTANGLE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<PhongMaterial>& pFloorMaterial =
		make_shared<PhongMaterial>(VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	pFloorMaterial->setDiffuseTexture(pFloor_diffuse);
	pFloorMaterial->useDiffuseTexture(true);
	pFloorMaterial->setShininess(150.f);

	unique_ptr<Mesh> pWoodToyMesh = make_unique<Mesh>(pFloorVA, pFloorMaterial);
	__pFloorRU = ruManager.createRenderUnit(move(pWoodToyMesh));

	Transform& floorTransform = __pFloorRU->getTransform();
	floorTransform.setScale(60.f, 60.f, 1.f);
	floorTransform.setRotation(-half_pi<float>(), 0.f, 0.f);

	__pBlubRU = AssetImporter::import("res/asset/bulb_fish/scene.gltf");
	__pBlubRU->setNumInstances(2);

	Transform &blub1Transform = __pBlubRU->getTransform(0);
	blub1Transform.setScale(3.f);
	blub1Transform.setPosition(0.f, 10.f, -20.f);
	blub1Transform.setRotation(0.f, pi<float>(), 0.f);

	Transform& blub2Transform = __pBlubRU->getTransform(1);
	blub2Transform.setScale(3.f);
	blub2Transform.setPosition(10.f, 3.f, 10.f);
	blub2Transform.setRotation(0.f, pi<float>() * 0.25f, 0.f);

	__pCargoBayRU = AssetImporter::import("res/asset/cargo_bay/scene.gltf");
	Transform &cargoBayTransform = __pCargoBayRU->getTransform();
	cargoBayTransform.setScale(10.f);
	cargoBayTransform.setPosition(0.f, 3.5f, 0.f);
	__pCargoBayRU->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	__pPulseCoreRU = AssetImporter::import("res/asset/arc_pulse_core/scene.gltf");
	Transform& pulseCoreTransform = __pPulseCoreRU->getTransform();
	pulseCoreTransform.setScale(3.f);
	pulseCoreTransform.setPosition(17.f, 0.f, 0.f);
	pulseCoreTransform.setRotation(-half_pi<float>(), 0.f, 0.f);
	__pPulseCoreRU->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	__pDoorRU = AssetImporter::import("res/asset/scifi_door/scene.gltf");
	Transform &doorTransform = __pDoorRU->getTransform();
	doorTransform.setScale(.1f);
	doorTransform.setPosition(0.f, 0.f, -30.f);
	doorTransform.setRotation(0.f, 0, 0.f);
	__pDoorRU->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 15.f, 50.f);
	cameraTransform.setRotation(-.4f, 0.f, 0.f);

	// Light 초기화

	__pWhiteLight = make_shared<PointLight>();
	__pWhiteLight->setAmbientStrength(.05f);
	__pWhiteLight->setDiffuseStrength(6.f);
	__pWhiteLight->setSpecularStrength(6.f);
	__pWhiteLight->setAttenuation(1.f, 0.07f, 0.017f);
	__pWhiteLight->setDepthMapSize(2048, 2048);
	__pWhiteLight->setShadowEnabled(true);

	Transform& whiteLightTransform = __pWhiteLight->getTransform();
	whiteLightTransform.setPosition(blub1Transform.getPosition() + vec3 { 0.f, 1.f, 3.5f });

	__pRedLight = make_shared<PointLight>();
	__pRedLight->setAlbedo(1.f, .3f, .2f);
	__pRedLight->setAmbientStrength(.05f);
	__pRedLight->setDiffuseStrength(6.f);
	__pRedLight->setSpecularStrength(6.f);
	__pRedLight->setAttenuation(1.f, 0.07f, 0.017f);
	__pRedLight->setDepthMapSize(2048, 2048);
	__pRedLight->setShadowEnabled(true);

	Transform& redLightTransform = __pRedLight->getTransform();
	redLightTransform.setPosition(blub2Transform.getPosition() + vec3{ -2.f, 1.f, -2.f });

	//// Deployer / Updater 초기화 ////

	__pLightHandler = make_shared<LightHandler>();
	__pLightHandler->addLight(__pWhiteLight);
	__pLightHandler->addLight(__pRedLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pFloorRU);
	__pUpdater->addUpdatable(__pBlubRU);
	__pUpdater->addUpdatable(__pCargoBayRU);
	__pUpdater->addUpdatable(__pPulseCoreRU);
	__pUpdater->addUpdatable(__pDoorRU);
	__pUpdater->addUpdatable(__pCamera);
	__pUpdater->addUpdatable(__pWhiteLight);
	__pUpdater->addUpdatable(__pRedLight);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pFloorRU);
	__pDrawer->addDrawable(__pBlubRU);
	__pDrawer->addDrawable(__pCargoBayRU);
	__pDrawer->addDrawable(__pPulseCoreRU);
	__pDrawer->addDrawable(__pDoorRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>();
	__pMsaaPP = make_shared<MSAAPostProcessor>();

	__pPPPipeline = make_shared<PostProcessingPipeline>();
	__pPPPipeline->appendProcessor(__pMsaaPP);
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