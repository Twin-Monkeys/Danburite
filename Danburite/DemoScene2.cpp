#include "DemoScene2.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderingContext.h"
#include "AssetImporter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "GLFunctionWrapper.h"
#include "VertexArrayFactory.h"
#include "TransparentPhongMaterial.h"
#include "TextureUtil.h"
#include "FrameBuffer.h"
#include "Constant.h"
#include <random>
#include "ReflectionMaterial.h"
#include "ReflectionPhongMaterial.h"
#include "RefractionMaterial.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

DemoScene2::DemoScene2()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::STENCIL_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);

	// Stencil mask 값이 0x00인 경우 Stencil Buffer clear bit도 0이 되어 버퍼 클리어도 안됨.
	// Depth mask도 같은 원리이다. (클리어 전 depth mask가 false이면 클리어 안됨.)
	// GLFunctionWrapper::setStencilMask(0xFF); -> 기본이므로 생략해도 무방.

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program &monoColorProgram = programFactory.getProgram(ProgramType::MONO_COLOR);
	Program &phongProgram = programFactory.getProgram(ProgramType::PHONG);
	Program &silhouetteProgram = programFactory.getProgram(ProgramType::SILHOUETTE);
	Program &outlineProgram = programFactory.getProgram(ProgramType::OUTLINE);
	Program &skyboxProgram = programFactory.getProgram(ProgramType::SKYBOX);
	Program &reflectionProgram = programFactory.getProgram(ProgramType::REFLECTION);
	Program &reflectionPhongProgram = programFactory.getProgram(ProgramType::REFLECTION_PHONG);
	Program &refractionProgram = programFactory.getProgram(ProgramType::REFRACTION);


	//// Uniform Buffer 생성 ////

	__pUBLight = make_shared<UniformBuffer>("UBLight", ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT);
	__pUBLight->enableZeroInit(true);
	__pUBLight->registerProgram(phongProgram);
	__pUBLight->registerProgram(reflectionPhongProgram);

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(monoColorProgram);
	__pUBCamera->registerProgram(phongProgram);
	__pUBCamera->registerProgram(silhouetteProgram);
	__pUBCamera->registerProgram(outlineProgram);
	__pUBCamera->registerProgram(skyboxProgram);
	__pUBCamera->registerProgram(reflectionProgram);
	__pUBCamera->registerProgram(reflectionPhongProgram);
	__pUBCamera->registerProgram(refractionProgram);


	//// Rendering unit 생성 ////

	RenderingUnitManager &ruManager = RenderingUnitManager::getInstance();

	__pNanosuitRU = AssetImporter::import(
		"res/asset/nanosuit/nanosuit.obj", Constant::Matrix::IDENTITY_MATRIX, MaterialType::REFRACTION);

	__pNanosuitRU->setNumInstances(25);

	for (int i = 0; i < 25; i++)
	{
		Transform &nanosuitTransform = __pNanosuitRU->getTransform(i);
		nanosuitTransform.setScale(.5f);
		nanosuitTransform.setPosition(5.f + ((i % 5) * 15.f), 16.4f, 10.f + ((i / 5) * 15.f));
	}

	mat4 starshipRotation = rotate(-half_pi<float>(), vec3{ 0.f, 1.f, 0.f });
	starshipRotation = rotate(starshipRotation, pi<float>(), vec3{ 1.f, 0.f, 0.f });
	__pStarshipRU = AssetImporter::import("res/asset/star_destroyer/scene.gltf", starshipRotation);
	__pStarshipRU->setNumInstances(6);

	Transform &starship1Transform = __pStarshipRU->getTransform(0);
	starship1Transform.setScale(.01f);

	Transform &starship2Transform = __pStarshipRU->getTransform(1);
	starship2Transform.setScale(.01f);
	starship2Transform.setPosition(-50.f, -20.f, -30.f);

	Transform &starship3Transform = __pStarshipRU->getTransform(2);
	starship3Transform.setScale(.01f);
	starship3Transform.setPosition(50.f, -20.f, -30.f);

	Transform &enemyShip1Transform = __pStarshipRU->getTransform(3);
	enemyShip1Transform.setScale(.01f);
	enemyShip1Transform.setPosition(0.f, 0.f, 200.f);
	enemyShip1Transform.setRotationAngle(pi<float>());

	Transform &enemyShip2Transform = __pStarshipRU->getTransform(4);
	enemyShip2Transform.setScale(.01f);
	enemyShip2Transform.setPosition(-50.f, -20.f, 230.f);
	enemyShip2Transform.setRotationAngle(pi<float>());

	Transform &enemyShip3Transform = __pStarshipRU->getTransform(5);
	enemyShip3Transform.setScale(.01f);
	enemyShip3Transform.setPosition(50.f, -20.f, 230.f);
	enemyShip3Transform.setRotationAngle(pi<float>());

	mat4 halconRotation = rotate(pi<float>(), vec3{ 0.f, 1.f, 0.f });
	halconRotation = rotate(halconRotation, -half_pi<float>(), vec3{ 1.f, 0.f, 0.f });
	__pHalconRU = AssetImporter::import("res/asset/halcon/scene.gltf", halconRotation);
	
	Transform &halconTransform = __pHalconRU->getTransform();
	halconTransform.setScale(.3f);
	halconTransform.setPosition(-100.f, -130.f, 300.f);
	halconTransform.adjustRotationAngle(half_pi<float>());

	mat4 fighterRotation = rotate(pi<float>(), vec3{ 0.f, 1.f, 0.f }); 
	fighterRotation = rotate(fighterRotation, -half_pi<float>(), vec3{ 1.f, 0.f, 0.f });
	fighterRotation = scale(fighterRotation, vec3 { .5f });
	__pFighterRU = AssetImporter::import("res/asset/federation_attack_fighter/scene.gltf", fighterRotation);
	__pFighterRU->setNumInstances(NUM_FIGHTERS);

	default_random_engine randEngine;
	uniform_real_distribution<float> realDist;
	for (size_t i = 0; i < NUM_FIGHTERS; i++)
	{
		vec3 randPos
		{
			(realDist(randEngine) - .5f) * .2f,
			(realDist(randEngine) - .5f) * .2f,
			realDist(randEngine) - .5f
		};

		__pFighterRU->getTransform(i).setPosition(randPos * 1500.f);

		__arrFighterRUDirection[i] =
		{
			(realDist(randEngine) - .5f) * .2f,
			(realDist(randEngine) - .5f) * .2f,
			(realDist(randEngine) * 5.f) + 2.f
		};
	}

	mat4 mercuryRotation = rotate(half_pi<float>(), vec3{ 1.f, 0.f, 0.f });
	__pMercuryRU = AssetImporter::import("res/asset/mercury_planet/scene.gltf", mercuryRotation);
	Transform &mercuryTransform = __pMercuryRU->getTransform();
	mercuryTransform.setScale(50.f);
	mercuryTransform.setPosition(70.f, 80.f, 850.f);
	mercuryTransform.setRotationAxis({ .3f, 1.f, 0.f });

	__pJupiterRU = AssetImporter::import("res/asset/jupiter/scene.gltf", mercuryRotation);
	Transform &jupiterTransform = __pJupiterRU->getTransform();
	jupiterTransform.setScale(100.f);
	jupiterTransform.setPosition(130.f, -90.f, -850.f);
	jupiterTransform.setRotationAxis({ -.3f, 1.f, 0.f });

	__pVenusRU = AssetImporter::import("res/asset/venus/scene.gltf", mercuryRotation);
	Transform &venusTransform = __pVenusRU->getTransform();
	venusTransform.setScale(50.f);
	venusTransform.setPosition(-730.f, 40.f, -350.f);
	venusTransform.setRotationAxis({ .3f, -1.f, 0.2f });


	//// 조명 생성 ////

	__pDirectionalLight = make_shared<DirectionalLight>(*__pUBLight);
	__pDirectionalLight->setDirection(1.f, -1.f, 0.f);
	__pDirectionalLight->setAlbedo(.3f, .5f, .9f);
	__pDirectionalLight->setAmbientStrength(.2f);
	__pDirectionalLight->setDiffuseStrength(2.f);
	__pDirectionalLight->setSpecularStrength(2.f);


	//// 카메라 생성 ////

	__pCamera = make_shared<SimpleCamera>();
	__pCamera->setPosition(15.f, 15.f, 25.f);
	__pCamera->pitch(-quarter_pi<float>() * .2f);
	__pCamera->yaw(quarter_pi<float>() * .7f);

	// Skybox 생성

	const shared_ptr<TextureCubemap> &pSkyboxAlbedoTex =
		TextureUtil::createTextureCubemapFromImage(
			{
				"res/image/skybox/space/right.png",
				"res/image/skybox/space/left.png",
				"res/image/skybox/space/top.png",
				"res/image/skybox/space/bot.png",
				"res/image/skybox/space/front.png",
				"res/image/skybox/space/back.png"
			});

	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
	pSkyboxAlbedoTex->setState(TextureParamType::TEXTURE_WRAP_R, TextureWrapValue::CLAMP_TO_EDGE);

	__pSkybox = make_shared<CubeSkybox>();
	__pSkybox->setAlbedoTexture(pSkyboxAlbedoTex);

	__pNanosuitRU->traverseMaterial<RefractionMaterial>(
		&RefractionMaterial::setEnvironmentTexture, pSkyboxAlbedoTex);

	//// Deployer / Updater 초기화 ////

	__pUBCamera->addDeployable(__pCamera);

	__pLightDeployer = make_shared<LightDeployer>();
	__pLightDeployer->addLight(__pDirectionalLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pNanosuitRU);
	__pUpdater->addUpdatable(__pStarshipRU);
	__pUpdater->addUpdatable(__pHalconRU);
	__pUpdater->addUpdatable(__pMercuryRU);
	__pUpdater->addUpdatable(__pJupiterRU);
	__pUpdater->addUpdatable(__pVenusRU);
	__pUpdater->addUpdatable(__pFighterRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pNanosuitRU);
	__pDrawer->addDrawable(__pStarshipRU);
	__pDrawer->addDrawable(__pHalconRU);
	__pDrawer->addDrawable(__pMercuryRU);
	__pDrawer->addDrawable(__pJupiterRU);
	__pDrawer->addDrawable(__pVenusRU);
	__pDrawer->addDrawable(__pFighterRU);
}

void DemoScene2::__keyFunc(const float deltaTime) noexcept
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
}

void DemoScene2::draw() noexcept
{
	__pUBCamera->batchDeploy();
	__pLightDeployer->batchDeploy();

	GLFunctionWrapper::clearBuffers(FrameBufferClearFlag::COLOR_DEPTH_STENCIL);

	__pDrawer->batchDraw();

	// 배경은 불투명한 물체가 모두 그려진 뒤 그림. (frag shader running 최소화)
	__pSkybox->draw();

	RenderingContext::requestBufferSwapping();
}

void DemoScene2::delta(const float deltaTime) noexcept
{
	__keyFunc(deltaTime);

	const float MOVE_SPEED = (deltaTime * .08f);
	constexpr float BOUNDARY = 1300.f;

	for (size_t i = 0; i < NUM_FIGHTERS; i++)
	{
		Transform &fighterTransform = __pFighterRU->getTransform(i);
		fighterTransform.adjustPosition(__arrFighterRUDirection[i] * MOVE_SPEED);

		const vec3 &fighterPos = fighterTransform.getPosition();

		if (fighterPos.x < -BOUNDARY)
			fighterTransform.adjustPositionX(BOUNDARY * 2.f);
		else if (fighterPos.x > BOUNDARY)
			fighterTransform.adjustPositionX(-BOUNDARY * 2.f);

		if (fighterPos.y < -BOUNDARY)
			fighterTransform.adjustPositionY(BOUNDARY * 2.f);
		else if (fighterPos.y > BOUNDARY)
			fighterTransform.adjustPositionY(-BOUNDARY * 2.f);

		if (fighterPos.z < -BOUNDARY)
			fighterTransform.adjustPositionZ(BOUNDARY * 2.f);
		else if (fighterPos.z > BOUNDARY)
			fighterTransform.adjustPositionZ(-BOUNDARY * 2.f);
	}

	const float ROTATION_SPEED = (deltaTime * .00002f);
	__pMercuryRU->getTransform().adjustRotationAngle(ROTATION_SPEED);
	__pJupiterRU->getTransform().adjustRotationAngle(ROTATION_SPEED);
	__pVenusRU->getTransform().adjustRotationAngle(ROTATION_SPEED);
}

void DemoScene2::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void DemoScene2::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void DemoScene2::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	glViewport(0, 0, width, height);
	__pCamera->setAspectRatio(width, height);
}

void DemoScene2::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	__pCamera->yaw(xDelta * ROTATION_SPEED);
	__pCamera->pitch(yDelta * ROTATION_SPEED);
}

void DemoScene2::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void DemoScene2::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

void DemoScene2::onIdle(const float deltaTime) noexcept
{
	delta(deltaTime);
	update();
}