#include "BlinnPhongTestScene.h"
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

BlinnPhongTestScene::BlinnPhongTestScene()
{
	// 전역 옵션
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);


	// 프로그램 로딩

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program& phongProgram = programFactory.getProgram(ProgramType::PHONG);
	Program &gammaCorrectionProgram = programFactory.getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION);

	//// Uniform Buffer 생성 ////

	__pUBLight = make_shared<UniformBuffer>("UBLight", ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT);
	__pUBLight->enableZeroInit(true);
	__pUBLight->registerProgram(phongProgram);

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(phongProgram);

	__pUBGammaCorrection = make_shared<UniformBuffer>(
		"UBGammaCorrection", ShaderIdentifier::Value::UniformBlockBindingPoint::GAMMA_CORRECTION);

	__pUBGammaCorrection->registerProgram(gammaCorrectionProgram);


	//// Rendering unit 생성 ////

	RenderingUnitManager &ruManager = RenderingUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<VertexArray> &pFloorVA =
		vaFactory.getVertexArray(ShapeType::RECTANGLE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<Texture2D> &pFloorTexture = TextureUtil::createTexture2DFromImage("res/image/wood.png");

	pFloorTexture->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pFloorTexture->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pFloorTexture->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pFloorTexture->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<PhongMaterial> &pFloorMaterial = make_shared<PhongMaterial>(VertexAttributeType::POS3_COLOR4);
	pFloorMaterial->setAmbientTexture(pFloorTexture);
	pFloorMaterial->setDiffuseTexture(pFloorTexture);
	pFloorMaterial->setSpecularTexture(pFloorTexture);
	pFloorMaterial->setShininess(80.f);

	unique_ptr<Mesh> pMesh = make_unique<Mesh>(pFloorVA, pFloorMaterial);
	__pFloorRU = ruManager.createRenderingUnit(move(pMesh));

	Transform &floorTransform = __pFloorRU->getTransform();
	floorTransform.setScale(20.f);
	floorTransform.setRotation(-half_pi<float>(), { 1.f, 0.f, 0.f });


	//// 카메라 생성 ////

	__pCamera = make_shared<SimpleCamera>();
	__pCamera->setPosition(10.f, 10.f, 10.f);
	__pCamera->pitch(-quarter_pi<float>() * .7f);
	__pCamera->yaw(quarter_pi<float>());

	__pUBCamera->addDeployable(__pCamera);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pCamera);


	// Light 초기화

	for (size_t i = 0; i < __arrPointLight.size(); i++)
	{
		shared_ptr<PointLight> &pPointLight = __arrPointLight[i];

		pPointLight = make_shared<PointLight>(*__pUBLight);
		pPointLight->setPosition(-15.f + 10.f * float(i), 2.f, 0.f);
		pPointLight->setAttenuation(1.f, .07f, .017f);
		pPointLight->setAlbedo(1.f, 1.f, 1.f);
		pPointLight->setAmbientStrength(.05f);
	}

	//// Deployer / Updater 초기화 ////

	__pLightDeployer = make_shared<LightDeployer>();

	for (const shared_ptr<PointLight> &pPointLight : __arrPointLight)
		__pLightDeployer->addLight(pPointLight);

	__pUBCamera->addDeployable(__pCamera);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pFloorRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pFloorRU);

	__pGammaCorrectionPP = make_shared<GammaCorrectionPostProcessor>(*__pUBGammaCorrection);
}

void BlinnPhongTestScene::__keyFunc(const float deltaTime) noexcept
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
		__pCamera->moveHorizontal(-MOVE_SPEED);
	
	if (RIGHT)
		__pCamera->moveHorizontal(MOVE_SPEED);

	if (FRONT)
		__pCamera->moveForward(MOVE_SPEED);

	if (BACK)
		__pCamera->moveForward(-MOVE_SPEED);

	if (UP)
		__pCamera->moveVertical(MOVE_SPEED);

	if (DOWN)
		__pCamera->moveVertical(-MOVE_SPEED);

	const bool
		KEY_1	= (GetAsyncKeyState('1') & 0x8000),
		KEY_2	= (GetAsyncKeyState('2') & 0x8000),
		KEY_3	= (GetAsyncKeyState('3') & 0x8000);

	if (KEY_1)
		__pGammaCorrectionPP->setGamma(1.f);

	if (KEY_2)
		__pGammaCorrectionPP->setGamma(1.5f);

	if (KEY_3)
		__pGammaCorrectionPP->setGamma(2.2f);
}

void BlinnPhongTestScene::draw() noexcept
{
	__pLightDeployer->batchDeploy();
	__pUBCamera->batchDeploy();

	__pGammaCorrectionPP->bind();
	GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

	__pDrawer->batchDraw();

	PostProcessor::unbind();
	__pGammaCorrectionPP->render();

	RenderingContext::requestBufferSwapping();
}

void BlinnPhongTestScene::delta(const float deltaTime) noexcept
{
	__keyFunc(deltaTime);
}

void BlinnPhongTestScene::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void BlinnPhongTestScene::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void BlinnPhongTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	glViewport(0, 0, width, height);
	__pCamera->setAspectRatio(width, height);
	__pGammaCorrectionPP->setScreenSize(width, height);
}

void BlinnPhongTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	__pCamera->yaw(xDelta * ROTATION_SPEED);
	__pCamera->pitch(yDelta * ROTATION_SPEED);
}

void BlinnPhongTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void BlinnPhongTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

void BlinnPhongTestScene::onIdle(const float deltaTime) noexcept
{
	delta(deltaTime);
	update();
}