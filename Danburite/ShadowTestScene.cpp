#include "ShadowTestScene.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderingContext.h"
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
	// ���� �ɼ�

	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	// ���α׷� �ε�

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program& phongProgram = programFactory.getProgram(ProgramType::PHONG);
	Program &gammaCorrectionProgram = programFactory.getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION);
	Program &depthBakingProgram = programFactory.getProgram(ProgramType::DEPTH_BAKING);

	//// Uniform Buffer ���� ////

	__pUBLight = make_shared<UniformBuffer>("UBLight", ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT);
	__pUBLight->enableZeroInit(true);
	__pUBLight->registerProgram(phongProgram);

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(phongProgram);
	__pUBCamera->registerProgram(depthBakingProgram);

	__pUBGammaCorrection = make_shared<UniformBuffer>(
		"UBGammaCorrection", ShaderIdentifier::Value::UniformBlockBindingPoint::GAMMA_CORRECTION);

	__pUBGammaCorrection->registerProgram(gammaCorrectionProgram);


	//// Rendering unit ���� ////

	RenderingUnitManager &ruManager = RenderingUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<VertexArray> &pFloorVA =
		vaFactory.getVertexArray(ShapeType::RECTANGLE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<Texture2D> &pWoodTexture = TextureUtil::createTexture2DFromImage("res/image/wood.png");

	pWoodTexture->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pWoodTexture->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pWoodTexture->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pWoodTexture->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<PhongMaterial> &pFloorMaterial = make_shared<PhongMaterial>(VertexAttributeType::POS3_COLOR4);
	pFloorMaterial->setDiffuseTexture(pWoodTexture);

	unique_ptr<Mesh> pFloorMesh = make_unique<Mesh>(pFloorVA, pFloorMaterial);
	__pFloorRU = ruManager.createRenderingUnit(move(pFloorMesh));

	Transform &floorTransform = __pFloorRU->getTransform();
	floorTransform.setScale(20.f);
	floorTransform.setRotation(-half_pi<float>(), { 1.f, 0.f, 0.f });

	const shared_ptr<VertexArray> &pCubeVA =
		vaFactory.getVertexArray(ShapeType::CUBE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<PhongMaterial> &pCubeMaterial =
		make_shared<PhongMaterial>(VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	pCubeMaterial->setDiffuseTexture(pWoodTexture);

	unique_ptr<Mesh> pCubeMesh = make_unique<Mesh>(pCubeVA, pCubeMaterial);
	__pCubeRU = ruManager.createRenderingUnit(move(pCubeMesh));
	__pCubeRU->setNumInstances(3);

	Transform &cube1Transform = __pCubeRU->getTransform(0);
	cube1Transform.setPosition(5.f, 2.f, 0.f);

	Transform &cube2Transform = __pCubeRU->getTransform(1);
	cube2Transform.setScale(.6f);
	cube2Transform.setPosition(5.f, 5.f, 5.f);
	cube2Transform.setRotation(quarter_pi<float>() * 1.2f, { 1.f, 2.f, 1.f });

	Transform &cube3Transform = __pCubeRU->getTransform(2);
	cube3Transform.setScale(3.f);
	cube3Transform.setPosition(-5.f, 6.f, 5.f);
	cube3Transform.setRotation(quarter_pi<float>() * .3f, { -3.f, 1.f, 1.f });


	//// ī�޶� ���� ////

	__pMainCamera = make_shared<SimpleCamera>();
	__pMainCamera->setPosition(10.f, 10.f, 10.f);
	__pMainCamera->pitch(-quarter_pi<float>() * .7f);
	__pMainCamera->yaw(quarter_pi<float>());

	__pDepthBakingCamera = make_shared<DepthBakingCamera>();
	__pDepthBakingCamera->setPosition(0.f, 10.f, 0.f);


	// Light �ʱ�ȭ

	__pDirectionalLight = make_shared<DirectionalLight>(*__pUBLight);
	__pDirectionalLight->setDirection(1.f, -1.f, 1.f);
	__pDirectionalLight->setAmbientStrength(.05f);
	__pDirectionalLight->setDiffuseStrength(.3f);

	__pDepthBakingCamera->setDirection(__pDirectionalLight->getDirection());


	//// Deployer / Updater �ʱ�ȭ ////

	__pLightDeployer = make_shared<LightDeployer>();
	__pLightDeployer->addLight(__pDirectionalLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pFloorRU);
	__pUpdater->addUpdatable(__pCubeRU);
	__pUpdater->addUpdatable(__pMainCamera);
	__pUpdater->addUpdatable(__pDepthBakingCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pFloorRU);
	__pDrawer->addDrawable(__pCubeRU);

	__pDepthBaker = make_shared<DepthBaker>();

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>(*__pUBGammaCorrection);
	Material::setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);
}

void ShadowTestScene::__keyFunc(const float deltaTime) noexcept
{
	const bool ESC = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
	if (ESC)
		RenderingContext::requestScreenClose();

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

	if (LEFT)
		__pMainCamera->moveHorizontal(-MOVE_SPEED);
	
	if (RIGHT)
		__pMainCamera->moveHorizontal(MOVE_SPEED);

	if (FRONT)
		__pMainCamera->moveForward(MOVE_SPEED);

	if (BACK)
		__pMainCamera->moveForward(-MOVE_SPEED);

	if (UP)
		__pMainCamera->moveVertical(MOVE_SPEED);

	if (DOWN)
		__pMainCamera->moveVertical(-MOVE_SPEED);
}

void ShadowTestScene::draw() noexcept
{
	// Depth baking
	{
		__pUBCamera->directDeploy(*__pDepthBakingCamera);
		Material::setRenderType(MaterialRenderType::DEPTH_BAKING);

		__pDepthBaker->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::DEPTH);

		__pDrawer->batchDraw();
		__pDepthBaker->unbind();

		// __pDepthBaker->getDepthAttachment();
	}

	// Gamma correction
	{
		__pLightDeployer->batchDeploy();

		__pUBCamera->directDeploy(*__pMainCamera);
		Material::setRenderType(MaterialRenderType::NORMAL);

		__pGammaCorrectionPP->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		__pDrawer->batchDraw();
		PostProcessor::unbind();
	}

	// Render to screen
	__pGammaCorrectionPP->render();
	RenderingContext::requestBufferSwapping();
}

void ShadowTestScene::delta(const float deltaTime) noexcept
{
	__keyFunc(deltaTime);
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

	__pMainCamera->setAspectRatio(width, height);
	__pDepthBaker->setScreenSize(width, height);
	__pGammaCorrectionPP->setScreenSize(width, height);
}

void ShadowTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	__pMainCamera->yaw(xDelta * ROTATION_SPEED);
	__pMainCamera->pitch(yDelta * ROTATION_SPEED);
}

void ShadowTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pMainCamera->resetFov();
}

void ShadowTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pMainCamera->adjustFov(ZOOM_SPEED * zDelta);
}

void ShadowTestScene::onIdle(const float deltaTime) noexcept
{
	delta(deltaTime);
	update();
}