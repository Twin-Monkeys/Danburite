#include "HDRTestScene.h"
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

	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<Texture2D>& pFloor_diffuse =
		TextureUtil::createTexture2DFromImage("res/image/metal.jpg");

	pFloor_diffuse->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pFloor_diffuse->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pFloor_diffuse->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pFloor_diffuse->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<VertexArray>& pFloorVA = vaFactory.getVertexArrayPtr(
			ShapeType::RECTANGLE, VertexAttributeFlag::POS | VertexAttributeFlag::NORMAL | VertexAttributeFlag::TEXCOORD);

	const shared_ptr<PhongMaterial>& pFloorMaterial = make_shared<PhongMaterial>(
		VertexAttributeFlag::POS | VertexAttributeFlag::NORMAL | VertexAttributeFlag::TEXCOORD);

	pFloorMaterial->setDiffuseTexture(pFloor_diffuse);
	pFloorMaterial->useDiffuseTexture(true);
	pFloorMaterial->setShininess(150.f);

	__pFloorObj = make_shared<SceneObject>();
	__pFloorObj->createNode(pFloorVA, pFloorMaterial);

	Transform& floorTransform = __pFloorObj->getTransform();
	floorTransform.setScale(60.f, 60.f, 1.f);
	floorTransform.setRotation(-half_pi<float>(), 0.f, 0.f);

	__pLampObj = AssetImporter::import("res/asset/bulb_fish/scene.gltf");
	__pLampObj->setNumInstances(2);

	Transform &lamp1Transform = __pLampObj->getTransform(0);
	lamp1Transform.setScale(.01f);
	lamp1Transform.setPosition(0.f, 10.f, -28.f);

	Transform &lamp2Transform = __pLampObj->getTransform(1);
	lamp2Transform.setScale(.01f);
	lamp2Transform.setPosition(10.f, 3.f, 10.f);
	lamp2Transform.setRotation(0.f, pi<float>(), 0.f);

	__pCargoBayObj = AssetImporter::import("res/asset/cargo_bay/scene.gltf");
	Transform &cargoBayTransform = __pCargoBayObj->getTransform();
	cargoBayTransform.setScale(10.f);
	cargoBayTransform.setPosition(0.f, 3.5f, 0.f);
	__pCargoBayObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	__pPulseCoreObj = AssetImporter::import("res/asset/arc_pulse_core/scene.gltf");
	Transform& pulseCoreTransform = __pPulseCoreObj->getTransform();
	pulseCoreTransform.setScale(6.f);
	pulseCoreTransform.setPosition(18.f, 0.f, 0.f);
	__pPulseCoreObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	__pDoorObj = AssetImporter::import("res/asset/scifi_door/scene.gltf");
	Transform &doorTransform = __pDoorObj->getTransform();
	doorTransform.setScale(.1f);
	doorTransform.setPosition(0.f, 0.f, -35.f);
	__pDoorObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	__pDoorObj->getAnimationManager().activateAnimation(1);
	__pDoorObj->getAnimationManager().getActiveAnimation().setPlaySpeed(.6f);

	__pLizardObj = AssetImporter::import("res/asset/lizard_man/scene.gltf");
	Transform &lizardTransform = __pLizardObj->getTransform();
	lizardTransform.setScale(7.f);
	lizardTransform.setPosition(-10.f, 8.f, 10.f);

	__pGirlObj = AssetImporter::import("res/asset/nuclear_hammer_girl/scene.gltf");
	__pGirlObj->setNumInstances(3);

	Transform &girlTransform = __pGirlObj->getTransform(0);
	girlTransform.setScale(5.f);
	girlTransform.setPosition(-12.f, 0.f, 20.f);

	Transform &girl2Transform = __pGirlObj->getTransform(1);
	girl2Transform = girlTransform;
	girl2Transform.adjustPosition(12.f, 0.f, 0.f);

	Transform &girl3Transform = __pGirlObj->getTransform(2);
	girl3Transform = girl2Transform;
	girl3Transform.adjustPosition(12.f, 0.f, 0.f);

	AnimationManager &girlAnimMgr = __pGirlObj->getAnimationManager();
	girlAnimMgr.activateAnimation(1);
	
	Animation &girlAnim = girlAnimMgr.getActiveAnimation();
	girlAnim.setPlaySpeed(.7f);
	girlAnim.setRepeatCount(-1);


	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform &cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 15.f, 50.f);
	cameraTransform.setRotation(-0.4f, 0.f, 0.f);

	// Light 초기화

	__pBlueLight = make_shared<PointLight>();
	__pBlueLight->setAlbedo(.2f, .3f, 1.f);
	__pBlueLight->setAmbientStrength(.05f);
	__pBlueLight->setDiffuseStrength(1.f);
	__pBlueLight->setSpecularStrength(1.f);
	__pBlueLight->setAttenuation(1.f, 0.09f, 0.032f);
	__pBlueLight->setDepthMapSize(2048, 2048);
	__pBlueLight->setShadowEnabled(true);

	Transform& blueLightTransform = __pBlueLight->getTransform();
	blueLightTransform.setPosition(lamp1Transform.getPosition() + vec3 { 0.f, .3f, 3.5f });

	__pRedLight = make_shared<PointLight>();
	__pRedLight->setAlbedo(1.f, .1f, .1f);
	__pRedLight->setAmbientStrength(.05f);
	__pRedLight->setDiffuseStrength(2.f);
	__pRedLight->setSpecularStrength(2.f);
	__pRedLight->setAttenuation(1.f, 0.22f, 0.20f);
	__pRedLight->setDepthMapSize(2048, 2048);
	__pRedLight->setShadowEnabled(true);

	Transform &redLightTransform = __pRedLight->getTransform();
	redLightTransform.setPosition(lamp2Transform.getPosition() + vec3{ -2.f, .3f, -2.f });

	//// Deployer / Updater 초기화 ////

	__pLightHandler = make_shared<LightHandler>();
	__pLightHandler->addLight(__pBlueLight);
	__pLightHandler->addLight(__pRedLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pFloorObj);
	__pUpdater->addUpdatable(__pLampObj);
	__pUpdater->addUpdatable(__pCargoBayObj);
	__pUpdater->addUpdatable(__pPulseCoreObj);
	__pUpdater->addUpdatable(__pDoorObj);
	__pUpdater->addUpdatable(__pLizardObj);
	__pUpdater->addUpdatable(__pGirlObj);
	__pUpdater->addUpdatable(__pCamera);
	__pUpdater->addUpdatable(__pBlueLight);
	__pUpdater->addUpdatable(__pRedLight);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pFloorObj);
	__pDrawer->addDrawable(__pLampObj);
	__pDrawer->addDrawable(__pCargoBayObj);
	__pDrawer->addDrawable(__pPulseCoreObj);
	__pDrawer->addDrawable(__pDoorObj);
	__pDrawer->addDrawable(__pLizardObj);
	__pDrawer->addDrawable(__pGirlObj);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>();
	__pHDRPP = make_shared<HDRPostProcessor>();
	__pMsaaPP = make_shared<MSAAPostProcessor>();

	__pPPPipeline = make_shared<PostProcessingPipeline>();
	__pPPPipeline->appendProcessor(__pMsaaPP);
	__pPPPipeline->appendProcessor(__pGammaCorrectionPP);
	__pPPPipeline->appendProcessor(__pHDRPP);

	UniformBufferFactory::getInstance().
		getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL).
		setUniformFloat(ShaderIdentifier::Name::Material::GAMMA, Constant::GammaCorrection::DEFAULT_GAMMA);
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

	Transform& cameraTransform = __pCamera->getTransform();

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
		__pHDRPP->setExposure(__pHDRPP->getExposure() - .05f);

	if (KEY2)
		__pHDRPP->setExposure(__pHDRPP->getExposure() + .05f);

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

bool HDRTestScene::update(const float deltaTime) noexcept
{
	constexpr vec3 pivot { 0.f, 0.f, 0.f };
	constexpr vec3 axis { 0.f, 1.f, 0.f };

	__pLampObj->getTransform().orbit(deltaTime * .0005f, pivot, axis);
	__pBlueLight->getTransform().orbit(deltaTime * .0005f, pivot, axis, false);

	const float doorDist =
		length(__pCamera->getTransform().getPosition() - __pDoorObj->getTransform().getPosition());

	if ((doorDist < 40.f) && !__doorOpened)
	{
		__doorOpened = true;

		Animation &doorAnim = __pDoorObj->getAnimationManager().getActiveAnimation();
		doorAnim.setPlayingOrder(AnimationPlayingOrderType::FORWARD, false);
		doorAnim.setRepeatCount(1);
	}
	else if ((doorDist > 40.f) && __doorOpened)
	{
		__doorOpened = false;

		Animation& doorAnim = __pDoorObj->getAnimationManager().getActiveAnimation();
		doorAnim.setPlayingOrder(AnimationPlayingOrderType::REVERSE, false);
		doorAnim.setRepeatCount(1);
	}

	__pUpdater->update(deltaTime);
	__updated = true;

	return __keyFunc(deltaTime);
}

void HDRTestScene::onDisplay() noexcept
{
	if (!__updated)
		return;
	
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

	Transform &cameraTransform = __pCamera->getTransform();
	cameraTransform.rotateFPS(-(yDelta * ROTATION_SPEED), -(xDelta * ROTATION_SPEED));
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
	return update(deltaTime);
}