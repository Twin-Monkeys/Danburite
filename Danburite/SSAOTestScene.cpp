#include "SSAOTestScene.h"
#include "VertexAttributeListFactory.h"
#include "RenderContext.h"
#include "AssetImporter.h"
#include "VertexArrayFactory.h"
#include "Constant.h"
#include "PhongMaterial.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ForwardRenderingPipeline.h"
#include "LightPrePassRenderingPipeline.h"
#include "GammaCorrectionPostProcessor.h"
#include "BloomPostProcessor.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

SSAOTestScene::SSAOTestScene()
{
	//// Rendering unit 생성 ////

	const shared_ptr<PhongMaterial> &pCommonMaterial = make_shared<PhongMaterial>(
		VertexAttributeFlag::POS | VertexAttributeFlag::COLOR | VertexAttributeFlag::NORMAL);

	pCommonMaterial->setShininess(150.f);

	const shared_ptr<VertexArray> &pFloorVA = VertexArrayFactory::createCircle(
		VertexAttributeFlag::POS | VertexAttributeFlag::COLOR | VertexAttributeFlag::NORMAL);

	__pFloorObj = make_shared<SceneObject>();
	__pFloorObj->createNode(pFloorVA, pCommonMaterial);

	Transform& floorTransform = __pFloorObj->getTransform();
	floorTransform.setScale(80.f, 1.f, 80.f);

	const shared_ptr<VertexArray> &pCylinderVA = VertexArrayFactory::createCylinder(
		VertexAttributeFlag::POS | VertexAttributeFlag::COLOR | VertexAttributeFlag::NORMAL, 2.f, 3.f, 2.f);

	__pCylinderObj = make_shared<SceneObject>();
	__pCylinderObj->createNode(pCylinderVA, pCommonMaterial);
	Transform &cylinderTransform = __pCylinderObj->getTransform();
	cylinderTransform.setScale(1.f);
	cylinderTransform.setPosition(-3.f, 0.f, -1.f);
	cylinderTransform.getRotation().set(0.1f, 1.f, 0.3f);

	const shared_ptr<VertexArray> &pSphereVA = VertexArrayFactory::createSphere(
		VertexAttributeFlag::POS | VertexAttributeFlag::COLOR | VertexAttributeFlag::NORMAL, 1.f);

	__pSphereObj = make_shared<SceneObject>();
	__pSphereObj->createNode(pSphereVA, pCommonMaterial);
	Transform &sphereTransform = __pSphereObj->getTransform();
	sphereTransform.setScale(3.f);
	sphereTransform.setPosition(4.f, 2.f, 3.f);

	const shared_ptr<VertexArray> &pCubeVA = VertexArrayFactory::createCube(
		VertexAttributeFlag::POS | VertexAttributeFlag::COLOR | VertexAttributeFlag::NORMAL, 1.f);

	__pCubeObj = make_shared<SceneObject>();
	__pCubeObj->createNode(pCubeVA, pCommonMaterial);
	Transform &cubeTransform = __pCubeObj->getTransform();
	cubeTransform.setScale(3.f);
	cubeTransform.setPosition(1.f, 1.f, 10.f);


	//// 카메라 초기화 ////

	Transform &cameraTransform = __camera.getTransform();
	cameraTransform.setPosition(0.f, 15.f, 50.f);
	cameraTransform.getRotation().set(-0.4f, pi<float>(), 0.f, EulerAngleOrder::YAW_PITCH_ROLL);


	// Light 초기화

	PointLight &light1 = __lightMgr.createLight<PointLight>();

	Transform& lightTransform = light1.getTransform();
	lightTransform.setPosition({ -10.f, 5.f, 5.f });
	// lightTransform.getRotation().set(-half_pi<float>() * .03f, pi<float>() * .8f, 0.f, EulerAngleOrder::YAW_PITCH_ROLL);

	light1.setAttenuation(1.f, .07f, .021f);
	light1.setAlbedo(.2f, .3f, 1.f);
	light1.setDiffuseStrength(3.f);
	light1.setSpecularStrength(3.f);
	light1.setShadowEnabled(true);

	//// Updater / Drawer 초기화 ////

	__updater.add(*__pFloorObj);
	__updater.add(*__pCylinderObj);
	__updater.add(*__pSphereObj);
	__updater.add(*__pCubeObj);
	__updater.add(__camera);
	__updater.add(light1);

	__drawer.add(*__pFloorObj);
	__drawer.add(*__pCylinderObj);
	__drawer.add(*__pSphereObj);
	__drawer.add(*__pCubeObj);


	// 파이프라인 초기화

	__pRenderingPipeline =
		make_unique<LightPrePassRenderingPipeline>(__lightMgr, __camera, __drawer);

	/*__pRenderingPipeline =
		make_unique<ForwardRenderingPipeline>(__lightMgr, __camera, __drawer);*/

	PostProcessorPipeline &ppPipeline =
		__pRenderingPipeline->getPostProcessorPipeline();

	/*
		감마 값은 기본적으로 필요. 1.f 라도 초기화 해주어야 함.
	*/
	ppPipeline.appendProcessor<GammaCorrectionPostProcessor>(true);
	// ppPipeline.appendProcessor<BloomPostProcessor>();
	__pHDRPP = &ppPipeline.appendProcessor<HDRPostProcessor>();
}

bool SSAOTestScene::__keyFunc(const float deltaTime) noexcept
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
		cameraTransform.moveHorizontal(MOVE_SPEED);

	if (RIGHT)
		cameraTransform.moveHorizontal(-MOVE_SPEED);

	if (FRONT)
		cameraTransform.moveForward(MOVE_SPEED);

	if (BACK)
		cameraTransform.moveForward(-MOVE_SPEED);

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

void SSAOTestScene::draw() noexcept
{
	__pRenderingPipeline->render();
	RenderContext::getCurrent()->requestBufferSwapping();
}

bool SSAOTestScene::update(const float deltaTime) noexcept
{
	__updater.process(&Updatable::update, deltaTime);
	__updated = true;

	return __keyFunc(deltaTime);
}

void SSAOTestScene::onDisplay() noexcept
{
	if (!__updated)
		return;

	draw();
}

void SSAOTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	__pRenderingPipeline->setScreenSize(width, height);
}

void SSAOTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform &cameraTransform = __camera.getTransform();
	cameraTransform.getRotation().
		rotateFPSPitch(yDelta * ROTATION_SPEED).
		rotateFPSYaw(-xDelta * ROTATION_SPEED);
}

void SSAOTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__camera.resetFov();
}

void SSAOTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__camera.adjustFov(ZOOM_SPEED * zDelta);
}

bool SSAOTestScene::onIdle(const float deltaTime) noexcept
{
	return update(deltaTime);
}