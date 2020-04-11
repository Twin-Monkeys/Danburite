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
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::MULTISAMPLE, true);
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	//// Rendering unit 생성 ////

	RenderUnitManager &ruManager = RenderUnitManager::getInstance();
	VertexArrayFactory &vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<VertexArray> &pFloorVA =
		vaFactory.getVertexArrayPtr(ShapeType::RECTANGLE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<Texture2D> &pFloorTexture = TextureUtil::createTexture2DFromImage("res/image/mosaic.jpg");
	pFloorTexture->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pFloorTexture->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pFloorTexture->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pFloorTexture->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<Texture2D> &pCubeTexture = TextureUtil::createTexture2DFromImage("res/image/box.jpg");
	pCubeTexture->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pCubeTexture->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pCubeTexture->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pCubeTexture->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<PhongMaterial> &pFloorMaterial = make_shared<PhongMaterial>(VertexAttributeType::POS3_COLOR4);
	pFloorMaterial->setDiffuseTexture(pFloorTexture);
	pFloorMaterial->useDiffuseTexture(true);
	pFloorMaterial->setShininess(150.f);

	unique_ptr<Mesh> pFloorMesh = make_unique<Mesh>(pFloorVA, pFloorMaterial);
	__pFloorRU = ruManager.createRenderUnit(move(pFloorMesh));

	Transform &floorTransform = __pFloorRU->getTransform();
	floorTransform.setScale(80.f, 1.f, 45.f);
	floorTransform.setRotation(-half_pi<float>(), 0.f, 0.f);

	const shared_ptr<VertexArray> &pCubeVA =
		vaFactory.getVertexArrayPtr(ShapeType::CUBE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<PhongMaterial> &pCubeMaterial = make_shared<PhongMaterial>(VertexAttributeType::POS3_NORMAL3_TEXCOORD2);
	pCubeMaterial->setDiffuseTexture(pCubeTexture);
	pCubeMaterial->useDiffuseTexture(true);
	pCubeMaterial->setShininess(150.f);

	unique_ptr<Mesh> pCubeMesh = make_unique<Mesh>(pCubeVA, pCubeMaterial);
	__pCubeRU = ruManager.createRenderUnit(move(pCubeMesh));
	__pCubeRU->setNumInstances(3);

	Transform &cube1Transform = __pCubeRU->getTransform(0);
	cube1Transform.setPosition(5.f, 1.f, -2.f);

	Transform &cube2Transform = __pCubeRU->getTransform(1);
	cube2Transform.setScale(5.f);
	cube2Transform.setPosition(5.f, 15.f, 5.f);
	cube2Transform.setRotation(1.f, 2.f, 1.f);

	Transform &cube3Transform = __pCubeRU->getTransform(2);
	cube3Transform.setScale(3.f);
	cube3Transform.setPosition(-5.f, 6.f, 5.f);
	cube3Transform.setRotation(-3.f, 1.f, 1.f);

	__pNanosuitRU = AssetImporter::import("res/asset/nanosuit/nanosuit.obj");
	Transform &nanosuitTransform = __pNanosuitRU->getTransform();
	nanosuitTransform.setPosition(-10.f, 0.f, 15.f);

	__pSkullRU = AssetImporter::import("res/asset/skull/scene.gltf");
	Transform &skullTransform = __pSkullRU->getTransform();
	skullTransform.setPosition(10.f, 5.f, 15.f);
	skullTransform.setRotation(-half_pi<float>(), 0.f, 0.f);
	skullTransform.setScale(5.f);


	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform &cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 5.f, 40.f);


	// Light 초기화

	__pRedLight = make_shared<DirectionalLight>();

	Transform &redLightTransform = __pRedLight->getTransform();
	redLightTransform.setPosition(20.f, 30.f, 0.f);
	redLightTransform.adjustRotation(-quarter_pi<float>(), 1.1f, 0.f);

	__pRedLight->setAlbedo(1.f, .4f, .4f);
	__pRedLight->setAmbientStrength(.05f);
	__pRedLight->setDiffuseStrength(.3f);
	__pRedLight->setSpecularStrength(1.f);

	/*
		You can reduce these blocky shadows
		By increasing the depth map resolution or
		By trying to fit the light frustum as closely to the scene as possible.
	*/
	__pRedLight->setDepthBakingOrthoHeight(100.f);
	__pRedLight->setDepthMapResolution(2048, 2048);
	__pRedLight->setShadowEnabled(true);

	__pWhiteLight = make_shared<DirectionalLight>();

	Transform& whiteLightTransform = __pWhiteLight->getTransform();
	whiteLightTransform.setPosition(-20.f, 30.f, 0.f);
	whiteLightTransform.adjustRotation(-quarter_pi<float>() * .7f, -.6f, 0.f);

	__pWhiteLight->setDepthBakingOrthoHeight(100.f);
	__pWhiteLight->setDepthMapResolution(2048, 2048);
	__pWhiteLight->setAmbientStrength(.05f);
	__pWhiteLight->setDiffuseStrength(.3f);
	__pWhiteLight->setSpecularStrength(1.f);
	__pWhiteLight->setShadowEnabled(true);

	//// Deployer / Updater 초기화 ////

	__pLightHandler = make_shared<LightHandler>();
	__pLightHandler->addLight(__pRedLight);
	__pLightHandler->addLight(__pWhiteLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pFloorRU);
	__pUpdater->addUpdatable(__pCubeRU);
	__pUpdater->addUpdatable(__pCamera);
	__pUpdater->addUpdatable(__pRedLight);
	__pUpdater->addUpdatable(__pWhiteLight);
	__pUpdater->addUpdatable(__pNanosuitRU);
	__pUpdater->addUpdatable(__pSkullRU);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pFloorRU);
	__pDrawer->addDrawable(__pCubeRU);
	__pDrawer->addDrawable(__pNanosuitRU);
	__pDrawer->addDrawable(__pSkullRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>();
	__pMsaaPP = make_shared<MSAAPostProcessor>();

	__pPPPipeline = make_shared<PostProcessingPipeline>();
	__pPPPipeline->appendProcessor(__pMsaaPP);
	__pPPPipeline->appendProcessor(__pGammaCorrectionPP);

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
	__pLightHandler->batchDeploy();
	__pLightHandler->batchBakeDepthMap(*__pDrawer);

	UniformBuffer &ubCamera =
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

bool ShadowTestScene::delta(const float deltaTime) noexcept
{
	__pCubeRU->getTransform(1).adjustRotation(deltaTime * .00015f, deltaTime * .0005f, 0.f);
	__pRedLight->getTransform().orbit(deltaTime * .0002f, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });
	__pWhiteLight->getTransform().orbit(-deltaTime * .0001f, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f });

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
	__pPPPipeline->setScreenSize(width, height);
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