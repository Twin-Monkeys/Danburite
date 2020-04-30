#include "ParallaxMapTestScene.h"
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

ParallaxMapTestScene::ParallaxMapTestScene()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::MULTISAMPLE, true);
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	//// Rendering unit 생성 ////

	RenderUnitManager& ruManager = RenderUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<Texture2D>& pWoodToyTexture_diffuse =
		TextureUtil::createTexture2DFromImage("res/image/wood_toy/wood_toy_diffuse.png");

	pWoodToyTexture_diffuse->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pWoodToyTexture_diffuse->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pWoodToyTexture_diffuse->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pWoodToyTexture_diffuse->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<Texture2D>& pWoodToyTexture_normal =
		TextureUtil::createTexture2DFromImage("res/image/wood_toy/wood_toy_normal.png");

	pWoodToyTexture_normal->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pWoodToyTexture_normal->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pWoodToyTexture_normal->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pWoodToyTexture_normal->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<Texture2D>& pWoodToyTexture_height =
		TextureUtil::createTexture2DFromImage("res/image/wood_toy/wood_toy_height.png");

	pWoodToyTexture_height->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pWoodToyTexture_height->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pWoodToyTexture_height->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pWoodToyTexture_height->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<VertexArray>& pWoodToyVA =
		vaFactory.getVertexArrayPtr(ShapeType::RECTANGLE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2_TANGENT3);

	const shared_ptr<PhongMaterial>& pWoodToyMaterial =
		make_shared<PhongMaterial>(VertexAttributeType::POS3_NORMAL3_TEXCOORD2_TANGENT3);

	pWoodToyMaterial->setDiffuseTexture(pWoodToyTexture_diffuse);
	pWoodToyMaterial->useDiffuseTexture(true);

	pWoodToyMaterial->setNormalTexture(pWoodToyTexture_normal);
	pWoodToyMaterial->useNormalTexture(true);

	pWoodToyMaterial->setHeightTexture(pWoodToyTexture_height);
	pWoodToyMaterial->useHeightTexture(true);

	pWoodToyMaterial->setShininess(150.f);

	unique_ptr<Mesh> pWoodToyMesh = make_unique<Mesh>(pWoodToyVA, pWoodToyMaterial);
	__pWoodToyRU = ruManager.createRenderUnit(move(pWoodToyMesh));

	Transform& woodToyTransform = __pWoodToyRU->getTransform();
	woodToyTransform.setScale(10.f, 10.f, 1.f);


	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.setPosition(0.f, 0.f, 30.f);

	// Light 초기화

	__pWhiteLight = make_shared<PointLight>();
	__pWhiteLight->setAmbientStrength(.05f);
	__pWhiteLight->setDiffuseStrength(2.f);
	__pWhiteLight->setSpecularStrength(2.f);
	__pWhiteLight->setAttenuation(1.f, 0.09f, 0.032f);

	Transform& whiteLightTransform = __pWhiteLight->getTransform();
	whiteLightTransform.setPosition(0.f, 6.f, 2.f);

	//// Deployer / Updater 초기화 ////

	__pLightHandler = make_shared<LightHandler>();
	__pLightHandler->addLight(__pWhiteLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pWoodToyRU);
	__pUpdater->addUpdatable(__pCamera);
	__pUpdater->addUpdatable(__pWhiteLight);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pWoodToyRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>();
	__pMsaaPP = make_shared<MSAAPostProcessor>();

	__pPPPipeline = make_shared<PostProcessingPipeline>();
	__pPPPipeline->appendProcessor(__pGammaCorrectionPP);

	UniformBufferFactory::getInstance().
		getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::MATERIAL).
		setUniformFloat(ShaderIdentifier::Name::Material::GAMMA, Constant::GammaCorrection::DEFAULT_GAMMA);
}

bool ParallaxMapTestScene::__keyFunc(const float deltaTime) noexcept
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

void ParallaxMapTestScene::draw() noexcept
{
	__pLightHandler->batchDeploy();

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

bool ParallaxMapTestScene::update(const float deltaTime) noexcept
{
	__pWhiteLight->getTransform().orbit(deltaTime * .0003f, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 1.f });
	__pUpdater->update(deltaTime);
	__updated = true;

	return __keyFunc(deltaTime);
}

void ParallaxMapTestScene::onDisplay() noexcept
{
	if (!__updated)
		return;

	draw();
}

void ParallaxMapTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	__pCamera->setAspectRatio(width, height);
	__pPPPipeline->setScreenSize(width, height);
}

void ParallaxMapTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform& cameraTransform = __pCamera->getTransform();
	cameraTransform.rotateGlobal(-(yDelta * ROTATION_SPEED), -(xDelta * ROTATION_SPEED), 0.f);
}

void ParallaxMapTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void ParallaxMapTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

bool ParallaxMapTestScene::onIdle(const float deltaTime) noexcept
{
	return update(deltaTime);
}