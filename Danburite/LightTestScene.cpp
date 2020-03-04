#include "LightTestScene.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderContext.h"
#include "AssetImporter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "GLFunctionWrapper.h"
#include "VertexArrayFactory.h"
#include "TransparentPhongMaterial.h"
#include "TextureUtil.h"
#include "FrameBuffer.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

LightTestScene::LightTestScene()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::STENCIL_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);
	GLFunctionWrapper::setClearColor(.05f, .05f, .05f);

	// Stencil mask 값이 0x00인 경우 Stencil Buffer clear bit도 0이 되어 버퍼 클리어도 안됨.
	// Depth mask도 같은 원리이다. (클리어 전 depth mask가 false이면 클리어 안됨.)
	// GLFunctionWrapper::setStencilMask(0xFF); -> 기본이므로 생략해도 무방.

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program &monoColorProgram = programFactory.getProgram(ProgramType::MONO_COLOR);
	Program &phongProgram = programFactory.getProgram(ProgramType::PHONG);
	Program &silhouetteProgram = programFactory.getProgram(ProgramType::SILHOUETTE);
	Program &outlineProgram = programFactory.getProgram(ProgramType::OUTLINE);
	Program &skyboxProgram = programFactory.getProgram(ProgramType::SKYBOX);
	Program &convProgram = programFactory.getProgram(ProgramType::POST_PROCESS_CONVOLUTIONAL);


	//// Uniform Buffer 생성 ////

	__pUBMaterial = make_shared<UniformBuffer>("UBMaterial", ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL);
	__pUBMaterial->registerProgram(monoColorProgram);
	__pUBMaterial->registerProgram(phongProgram);
	__pUBMaterial->registerProgram(silhouetteProgram);
	__pUBMaterial->registerProgram(outlineProgram);
	__pUBMaterial->registerProgram(skyboxProgram);

	__pUBLight = make_shared<UniformBuffer>("UBLight", ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT);
	__pUBLight->registerProgram(phongProgram);
	__pUBLight->enableZeroInit(true);

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(monoColorProgram);
	__pUBCamera->registerProgram(phongProgram);
	__pUBCamera->registerProgram(silhouetteProgram);
	__pUBCamera->registerProgram(outlineProgram);
	__pUBCamera->registerProgram(skyboxProgram);

	__pUBConv = make_shared<UniformBuffer>("UBConvolution", ShaderIdentifier::Value::UniformBlockBindingPoint::CONVOLUTION);
	__pUBConv->registerProgram(convProgram);
	__pUBConv->enableZeroInit(true);

	__pUBCubemap = make_shared<UniformBuffer>("UBCubemap", ShaderIdentifier::Value::UniformBlockBindingPoint::CUBEMAP);
	__pUBCubemap->registerProgram(skyboxProgram);


	//// Rendering unit 생성 ////

	RenderUnitManager &ruManager = RenderUnitManager::getInstance();

	const mat4 rotationMat = rotate(-half_pi<float>(), vec3 { 1.f, 0.f, 0.f });

	__pTerrainRU = AssetImporter::import("res/asset/mountain_terrain/Sasso.obj", *__pUBMaterial);
	Transform &terrainTransform = __pTerrainRU->getTransform();
	terrainTransform.setScale(5.f);

	__pNanosuitRU = AssetImporter::import("res/asset/nanosuit/nanosuit.obj", *__pUBMaterial);
	Transform &nanosuitTransform = __pNanosuitRU->getTransform();
	nanosuitTransform.setScale(.7f);
	nanosuitTransform.setPosition(15.f, -3.5f, 14.f);
	nanosuitTransform.adjustRotation(0.f, .7f, 0.f);
	
	__pLizardManRU = AssetImporter::import("res/asset/lizard_man/scene.gltf", *__pUBMaterial);
	Transform &lizardManTransform = __pLizardManRU->getTransform();
	lizardManTransform.setScale(4.f);
	lizardManTransform.adjustRotation(0.f, -.5f, 0.f);
	lizardManTransform.setPosition(-14.7f, 1.5f, 20.f);

	__pStreetLightRU = AssetImporter::import("res/asset/street_light/scene.gltf", *__pUBMaterial, rotationMat);
	Transform &streetLightTransform = __pStreetLightRU->getTransform();
	streetLightTransform.setPosition(-13.f, -2.f, -13.f);

	__pSkullRU = AssetImporter::import("res/asset/skull/scene.gltf", *__pUBMaterial);
	Transform &skullTransform = __pSkullRU->getTransform();
	skullTransform.setPosition(12.f, -1.8f, -5.f);
	skullTransform.setScale(5.f);
	skullTransform.setRotation(-half_pi<float>() * 1.4f, 0.f, 0.f);

	VertexArrayFactory &vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<VertexArray> &pCubeVA =
		vaFactory.getVertexArrayPtr(ShapeType::CUBE, VertexAttributeType::POS3_NORMAL3_TEXCOORD2);

	const shared_ptr<Texture2D> &pCubeTexture =
		TextureUtil::createTexture2DFromImage("res/image/blending_transparent_window.png");

	pCubeTexture->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR_MIPMAP_LINEAR);
	pCubeTexture->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pCubeTexture->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pCubeTexture->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);

	const shared_ptr<TransparentPhongMaterial> &pCubeMaterial =
		make_shared<TransparentPhongMaterial>(VertexAttributeType::POS3_NORMAL3_TEXCOORD2, *__pUBMaterial);

	pCubeMaterial->setDiffuseTexture(pCubeTexture);

	unique_ptr<Mesh> pMesh = make_unique<Mesh>(pCubeVA, pCubeMaterial);
	__pCubeRU = ruManager.createRenderUnit(move(pMesh));
	Transform &cubeTransform = __pCubeRU->getTransform();
	cubeTransform.setScale(3.f);
	cubeTransform.setPosition(-13.f, 7.f, -13.f);


	//// 조명 생성 ////

	__pDirectionalLight = make_shared<DirectionalLight>(*__pUBLight);
	__pDirectionalLight->setDirection(1.f, -1.f, 0.f);
	__pDirectionalLight->setAlbedo(.1f, .1f, .1f);

	__pStreetLight = make_shared<PointLight>(*__pUBLight);

	const vec3 &streetLightPos = streetLightTransform.getPosition();
	__pStreetLight->setPosition(streetLightPos.x, streetLightPos.y + 10.f, streetLightPos.z);
	__pStreetLight->setAttenuation(1.f, .07f, .017f);
	__pStreetLight->setAlbedo(.8f, .8f, .1f);
	__pStreetLight->setDiffuseStrength(2.f);
	__pStreetLight->setSpecularStrength(2.f);

	__pRedSpotLight = make_shared<SpotLight>(*__pUBLight);
	__pRedSpotLight->setPosition(35.f, 4.f, -35.f);
	__pRedSpotLight->setDirection(-1.f, -.3f, 1.f);
	__pRedSpotLight->setAttenuation(1.f, .014f, .0007f);
	__pRedSpotLight->setCutOff(.25f, .35f);
	__pRedSpotLight->setAlbedo(.7f, .2f, .1f);
	__pRedSpotLight->setDiffuseStrength(2.f);
	__pRedSpotLight->setSpecularStrength(2.f);

	__pGreenSpotLight = make_shared<SpotLight>(*__pUBLight);
	__pGreenSpotLight->setPosition(35.f, 4.f, 35.f);
	__pGreenSpotLight->setDirection(-1.f, -.3f, -1.f);
	__pGreenSpotLight->setAttenuation(1.f, .014f, .0007f);
	__pGreenSpotLight->setCutOff(.25f, .35f);
	__pGreenSpotLight->setAlbedo(.3f, .6f, .2f);
	__pGreenSpotLight->setDiffuseStrength(2.f);
	__pGreenSpotLight->setSpecularStrength(2.f);

	__pBlueSpotLight = make_shared<SpotLight>(*__pUBLight);
	__pBlueSpotLight->setPosition(-35.f, 4.f, 35.f);
	__pBlueSpotLight->setDirection(1.f, -.3f, -1.f);
	__pBlueSpotLight->setAttenuation(1.f, .014f, .0007f);
	__pBlueSpotLight->setCutOff(.25f, .35f);
	__pBlueSpotLight->setAlbedo(.1f, .1f, .8f);
	__pBlueSpotLight->setDiffuseStrength(2.f);
	__pBlueSpotLight->setSpecularStrength(2.f);

	__pRotatingLight = make_shared<PointLight>(*__pUBLight);
	__pRotatingLight->setPosition(25.f, 3.f, 0.f);
	__pRotatingLight->setAttenuation(1.f, .07f, .017f);
	__pRotatingLight->setAlbedo(.1f, .8f, .9f);
	__pRotatingLight->setDiffuseStrength(2.f);
	__pRotatingLight->setSpecularStrength(2.f);


	//// 카메라 생성 ////

	__pCamera = make_shared<PerspectiveCamera>();

	Transform& cameraTransform = __pCamera->getTransform();

	cameraTransform.setPosition(35.f, 20.f, 35.f);
	cameraTransform.setRotation(-quarter_pi<float>() * .7f, quarter_pi<float>(), 0.f);


	// Skybox 생성

	const shared_ptr<TextureCubemap> &pSkyboxAlbedoTex =
		TextureUtil::createTextureCubemapFromImage(
			{
				"res/image/skybox/forest/posx.jpg",
				"res/image/skybox/forest/negx.jpg",
				"res/image/skybox/forest/posy.jpg",
				"res/image/skybox/forest/negy.jpg",
				"res/image/skybox/forest/posz.jpg",
				"res/image/skybox/forest/negz.jpg"
			});

	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_R, TextureWrapValue::CLAMP_TO_EDGE);

	__pSkybox = make_shared<CubeSkybox>(*__pUBCubemap);
	__pSkybox->setAlbedoTexture(pSkyboxAlbedoTex);

	__pGrayscalePP = make_shared<GrayscalePostProcessor>();

	__pConvPP = make_shared<ConvolutionalPostProcessor>(*__pUBConv);
	__pConvPP->setKernel(Constant::Convolutional::sharpenKernel3x3, 3U);

	__pPPP = make_shared<PostProcessingPipeline>();
	__pPPP->appendProcessor(__pGrayscalePP);
	__pPPP->appendProcessor(__pConvPP);


	//// Deployer / Updater 초기화 ////

	__pUBCamera->addDeployable(__pCamera);

	__pLightDeployer = make_shared<LightDeployer>();
	__pLightDeployer->addLight(__pDirectionalLight);
	__pLightDeployer->addLight(__pStreetLight);
	__pLightDeployer->addLight(__pRedSpotLight);
	__pLightDeployer->addLight(__pGreenSpotLight);
	__pLightDeployer->addLight(__pBlueSpotLight);
	__pLightDeployer->addLight(__pRotatingLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pTerrainRU);
	__pUpdater->addUpdatable(__pNanosuitRU);
	__pUpdater->addUpdatable(__pLizardManRU);
	__pUpdater->addUpdatable(__pStreetLightRU);
	__pUpdater->addUpdatable(__pSkullRU);
	__pUpdater->addUpdatable(__pCubeRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pTerrainRU);
	__pDrawer->addDrawable(__pLizardManRU);
	__pDrawer->addDrawable(__pNanosuitRU);
	__pDrawer->addDrawable(__pStreetLightRU);
	__pDrawer->addDrawable(__pSkullRU);
}

bool LightTestScene::__keyFunc(const float deltaTime) noexcept
{
	const bool ESC = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
	if (ESC)
		return false;

	constexpr float MOVE_SPEED_FACTOR = .013f;
	const float MOVE_SPEED = (MOVE_SPEED_FACTOR * deltaTime);

	const bool
		LEFT	= (GetAsyncKeyState('A') & 0x8000),
		RIGHT	= (GetAsyncKeyState('D') & 0x8000),
		FRONT	= (GetAsyncKeyState('W') & 0x8000),
		BACK	= (GetAsyncKeyState('S') & 0x8000),
		UP		= (GetAsyncKeyState('E') & 0x8000),
		DOWN	= (GetAsyncKeyState('Q') & 0x8000);

	Transform& cameraTransform = __pCamera->getTransform();

	if (LEFT)
		cameraTransform.moveHorizontal(-MOVE_SPEED);

	if (RIGHT)
		cameraTransform.moveHorizontal(MOVE_SPEED);

	if (FRONT)
		cameraTransform.moveForward(MOVE_SPEED);

	if (BACK)
		cameraTransform.moveForward(-MOVE_SPEED);

	if (UP)
		cameraTransform.moveVertical(MOVE_SPEED);

	if (DOWN)
		cameraTransform.moveVertical(-MOVE_SPEED);

	return true;
}

void LightTestScene::draw() noexcept
{
	__pUBCamera->batchDeploy();
	__pLightDeployer->batchDeploy();

	__pPPP->bind();
	GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH_STENCIL);

	__pDrawer->batchDraw();

	// 배경은 불투명한 물체가 모두 그려진 뒤 그림. (frag shader running 최소화)
	// __pSkybox->draw();

	// 반투명한 물체들은 불투명한 물체(배경 포함)를 그린 이후에 그려야 함.
	//__pCubeRU->draw();

	PostProcessingPipeline::unbind();
	__pPPP->render();

	RenderContext::getCurrent()->requestBufferSwapping();
}

bool LightTestScene::delta(const float deltaTime) noexcept
{
	if (!__keyFunc(deltaTime))
		return false;

	const float ROTATION_SPEED = (deltaTime * .0005f);

	const vec3 &prevLightPos = __pRotatingLight->getPosition();

	__pRotatingLight->setPosition(
		(prevLightPos.x * cosf(ROTATION_SPEED)) - (prevLightPos.z * sinf(ROTATION_SPEED)),
		prevLightPos.y,
		(prevLightPos.x * sinf(ROTATION_SPEED)) + (prevLightPos.z * cosf(ROTATION_SPEED)));

	return true;
}

void LightTestScene::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void LightTestScene::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void LightTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	glViewport(0, 0, width, height);
	__pCamera->setAspectRatio(width, height);
	__pPPP->setScreenSize(width, height);
}

void LightTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform &cameraTransform = __pCamera->getTransform();
	cameraTransform.adjustRotation(yDelta * ROTATION_SPEED, xDelta * ROTATION_SPEED, 0.f);
}

void LightTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void LightTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

bool LightTestScene::onIdle(const float deltaTime) noexcept
{
	if (!delta(deltaTime))
		return false;

	update();
	return true;
}