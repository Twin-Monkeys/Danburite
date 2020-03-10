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

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

ShadowTestScene::ShadowTestScene()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	// 프로그램 로딩

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program& phongProgram = programFactory.getProgram(ProgramType::PHONG);
	Program &gammaCorrectionProgram = programFactory.getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION);
	Program &depthBakingProgram = programFactory.getProgram(ProgramType::DEPTH_BAKING);

	//// Uniform Buffer 생성 ////

	__pUBMaterial = make_shared<UniformBuffer>("UBMaterial", ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL);
	__pUBMaterial->registerProgram(phongProgram);

	__pUBLight = make_shared<UniformBuffer>("UBLight", ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT);
	__pUBLight->enableZeroInit(true);
	__pUBLight->registerProgram(phongProgram);

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(phongProgram);
	__pUBCamera->registerProgram(depthBakingProgram);

	__pUBGammaCorrection = make_shared<UniformBuffer>(
		"UBGammaCorrection", ShaderIdentifier::Value::UniformBlockBindingPoint::GAMMA_CORRECTION);

	__pUBGammaCorrection->registerProgram(gammaCorrectionProgram);


	//// Rendering unit 생성 ////

	RenderUnitManager &ruManager = RenderUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<VertexArray> &pFloorVA =
		vaFactory.getVertexArrayPtr(ShapeType::RECTANGLE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<Texture2D> &pWoodTexture = TextureUtil::createTexture2DFromImage("res/image/wood.png");

	pWoodTexture->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pWoodTexture->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pWoodTexture->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pWoodTexture->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<PhongMaterial> &pFloorMaterial =
		make_shared<PhongMaterial>(VertexAttributeType::POS3_COLOR4, *__pUBMaterial);

	pFloorMaterial->setDiffuseTexture(pWoodTexture);
	pFloorMaterial->useDiffuseTexture(true);

	unique_ptr<Mesh> pFloorMesh = make_unique<Mesh>(pFloorVA, pFloorMaterial);
	__pFloorRU = ruManager.createRenderUnit(move(pFloorMesh));

	Transform &floorTransform = __pFloorRU->getTransform();
	floorTransform.setScale(20.f);
	floorTransform.setRotation(-half_pi<float>(), 0.f, 0.f);

	const shared_ptr<VertexArray> &pCubeVA =
		vaFactory.getVertexArrayPtr(ShapeType::CUBE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<PhongMaterial> &pCubeMaterial =
		make_shared<PhongMaterial>(VertexAttributeType::POS3_NORMAL3_TEXCOORD2, *__pUBMaterial);

	pCubeMaterial->setDiffuseTexture(pWoodTexture);
	pCubeMaterial->useDiffuseTexture(true);

	unique_ptr<Mesh> pCubeMesh = make_unique<Mesh>(pCubeVA, pCubeMaterial);
	__pCubeRU = ruManager.createRenderUnit(move(pCubeMesh));
	__pCubeRU->setNumInstances(3);

	Transform &cube1Transform = __pCubeRU->getTransform(0);
	cube1Transform.setPosition(5.f, 2.f, 0.f);

	Transform &cube2Transform = __pCubeRU->getTransform(1);
	cube2Transform.setScale(.6f);
	cube2Transform.setPosition(5.f, 5.f, 5.f);
	cube2Transform.setRotation(1.f, 2.f, 1.f);

	Transform &cube3Transform = __pCubeRU->getTransform(2);
	cube3Transform.setScale(3.f);
	cube3Transform.setPosition(-5.f, 6.f, 5.f);
	cube3Transform.setRotation(-3.f, 1.f, 1.f);


	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 5.f, 40.f);


	// Light 초기화

	__pDirectionalLight = make_shared<DirectionalLight>(*__pUBLight);
	__pDirectionalLight->getTransform().adjustRotation(-1.f, 1.f, 0.f);
	__pDirectionalLight->setAmbientStrength(.05f);
	__pDirectionalLight->setDiffuseStrength(.3f);


	//// Deployer / Updater 초기화 ////

	__pLightDeployer = make_shared<LightDeployer>();
	__pLightDeployer->addLight(__pDirectionalLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pFloorRU);
	__pUpdater->addUpdatable(__pCubeRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pFloorRU);
	__pDrawer->addDrawable(__pCubeRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>(*__pUBGammaCorrection);
	Material::setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);
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
	// Gamma correction
	// __pLightDeployer->batchBakeDepthMap();

	__pLightDeployer->batchDeploy();
	__pUBCamera->directDeploy(*__pCamera);

	__pGammaCorrectionPP->bind();
	GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

	__pDrawer->batchDraw();
	PostProcessor::unbind();

	// Render to screen
	__pGammaCorrectionPP->render();
	RenderContext::getCurrent()->requestBufferSwapping();
}

bool ShadowTestScene::delta(const float deltaTime) noexcept
{
	return __keyFunc(deltaTime);
}

void ShadowTestScene::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
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
	__pGammaCorrectionPP->setScreenSize(width, height);
}

void ShadowTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.adjustRotation(-(yDelta * ROTATION_SPEED), -(xDelta * ROTATION_SPEED), 0.f);
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
	if (!delta(deltaTime))
		return false;

	update();
	return true;
}