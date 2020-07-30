#include "LightingTestScene.h"
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
#include "ForwardRenderingPipeline.h"
#include "LightPrePassRenderingPipeline.h"
#include "GammaCorrectionPostProcessor.h"
#include "BloomPostProcessor.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

LightingTestScene::LightingTestScene()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::MULTISAMPLE, true);
	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, true);


	//// Rendering unit 생성 ////

	__pCorridorObj = AssetImporter::import("res/asset/corridor/scene.gltf");
	__pCorridorObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);

	__pCargoBayObj = AssetImporter::import("res/asset/cargo_bay/scene.gltf");
	__pCargoBayObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);
	Transform &cargoBayTransform = __pCargoBayObj->getTransform();
	cargoBayTransform.setScale(8.f);
	cargoBayTransform.setPosition(9.f, 2.7f, 120.f);
	cargoBayTransform.setRotation(0.f, .3f, 0.f);

	__pPulseCoreObj = AssetImporter::import("res/asset/arc_pulse_core/scene.gltf");
	__pPulseCoreObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);
	__pPulseCoreObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 2.f);
	Transform& pulseCoreTransform = __pPulseCoreObj->getTransform();
	pulseCoreTransform.setScale(4.f);
	pulseCoreTransform.setPosition(-10.f, 0.2f, 30.f);

	__pWrenchObj = AssetImporter::import("res/asset/wrench/scene.gltf");
	__pWrenchObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);
	Transform &wrenchTransform = __pWrenchObj->getTransform();
	wrenchTransform.setScale(15.f);
	wrenchTransform.setPosition(-12.f, 0.f, 90.f);
	wrenchTransform.setRotation(0.f, -.7f, 0.f);

	__pDroneObj = AssetImporter::import("res/asset/scifi_drone/scene.gltf");
	__pDroneObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);
	__pDroneObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 2.f);
	__pDroneObj->setNumInstances(GLsizei(__NUM_DRONES));

	for (size_t droneIter = 0ULL; droneIter < __NUM_DRONES; droneIter++)
	{
		const float randPosX = __posDistributeX(__randEngine);
		const float randPosZ = __posDistributeZ(__randEngine);

		Transform &droneTransform = __pDroneObj->getTransform(droneIter);
		droneTransform.setScale(.002f);
		droneTransform.setPosition(randPosX, 1.f, randPosZ);
		droneTransform.setRotation(__randDistribute(__randEngine) * .2f, __randDistribute(__randEngine), 0.f);
	}

	__pSpotLightObj = AssetImporter::import("res/asset/stage_light/scene.gltf");
	__pSpotLightObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);
	__pSpotLightObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 3.f);
	Transform &spotLightObjTransform = __pSpotLightObj->getTransform();
	spotLightObjTransform.setScale(.7f);
	spotLightObjTransform.setPosition(16.f, 0.f, 15.f);
	spotLightObjTransform.setRotation(0.f, -pi<float>() * .3f, 0.f);

	__pCharacterObj = AssetImporter::import("res/asset/scifi_male/scene.gltf");
	__pCharacterObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setShininess, 150.f);
	__pCharacterObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 2.f);
	Transform &characterTransform = __pCharacterObj->getTransform();
	characterTransform.setScale(.1f);


	// 애니메이션 초기화

	AnimationManager &characterAnimMgr = __pCharacterObj->getAnimationManager();

	Animation &lookUpAnim = characterAnimMgr.getAnimation(__ANIM_IDX_LOOK_UP);
	lookUpAnim.setRepeatCount(-1);
	lookUpAnim.setPlaySpeed(.3f);
	lookUpAnim.setAnimationRepeatType(AnimationRepeatType::PINGPONG);

	Animation &leftWalkAnim = characterAnimMgr.getAnimation(__ANIM_IDX_WALK_LEFT);
	leftWalkAnim.setRepeatCount(-1);
	leftWalkAnim.setPlaySpeed(.8f);

	Animation &frontWalkAnim = characterAnimMgr.getAnimation(__ANIM_IDX_WALK_FRONT);
	frontWalkAnim.setRepeatCount(-1);
	frontWalkAnim.setPlaySpeed(.8f);


	//// 카메라 초기화 ////

	Transform &cameraTransform = __camera.getTransform();
	cameraTransform.setPosition(0.f, 30.f, 0.f);
	cameraTransform.setRotation(-0.5f, pi<float>(), 0.f);

	const vec3 &cameraPos = cameraTransform.getPosition();
	characterTransform.setPosition(cameraPos.x, cameraPos.y - __CHARACTER_DIST_Y, cameraPos.z + __CHARACTER_DIST_Z);


	// Light 초기화

	__pPointLight = &__lightMgr.createLight<PointLight>();
	__pPointLight->setAlbedo(.25f, .35f, .8f);
	__pPointLight->setAmbientStrength(0.f);
	__pPointLight->setDiffuseStrength(20.f);
	__pPointLight->setSpecularStrength(20.f);
	__pPointLight->setAttenuation(1.f, .35f, .44f);
	__pPointLight->setShadowEnabled(true);

	__pSpotLight = &__lightMgr.createLight<SpotLight>();
	__pSpotLight->setAlbedo(.32f, .88f, .96f);
	__pSpotLight->setAmbientStrength(.03f);
	__pSpotLight->setDiffuseStrength(50.f);
	__pSpotLight->setSpecularStrength(50.f);
	__pSpotLight->setAttenuation(1.f, .14f, .07f);
	__pSpotLight->setCutOff(.1f, .4f);
	__pSpotLight->setShadowEnabled(true);

	Transform &spotLightTransform = __pSpotLight->getTransform();
	spotLightTransform.setPosition(spotLightObjTransform.getPosition() + vec3{ 0.f, 4.f, 0.f });
	spotLightTransform.setRotation(spotLightObjTransform.getRotation());
	spotLightTransform.rotateLocal(.1f, 0.f, 0.f);

	Transform &pointLightTransform = __pPointLight->getTransform();
	pointLightTransform.setPosition(8.f, 5.f, 110.f);

	for (size_t smallLightIter = 0ULL; smallLightIter < __NUM_SMALL_LIGHTS; smallLightIter++)
	{
		const vec3 &randAlbedo =
		{
			__randDistribute(__randEngine),
			__randDistribute(__randEngine),
			__randDistribute(__randEngine)
		};

		PointLight &smallLight = __lightMgr.createLight<PointLight>();
		smallLight.setAlbedo(randAlbedo);
		smallLight.setAmbientStrength(0.f);
		smallLight.setDiffuseStrength(10.f);
		smallLight.setSpecularStrength(10.f);
		smallLight.setAttenuation(1.f, .7f, 1.8f);
		smallLight.setShadowEnabled(false);

		const float randPosX = __posDistributeX(__randEngine);
		const float randPosZ = __posDistributeZ(__randEngine);

		Transform &smallLightTransform = smallLight.getTransform();
		smallLightTransform.setPosition(randPosX, .3f, randPosZ);

		__updater.add(smallLight);
	}

	//// Updater / Drawer 초기화 ////

	__updater.add(__camera);
	__updater.add(*__pPointLight);
	__updater.add(*__pSpotLight);
	__updater.add(*__pCorridorObj);
	__updater.add(*__pCargoBayObj);
	__updater.add(*__pPulseCoreObj);
	__updater.add(*__pWrenchObj);
	__updater.add(*__pDroneObj);
	__updater.add(*__pSpotLightObj);
	__updater.add(*__pCharacterObj);

	__drawer.add(*__pCorridorObj);
	__drawer.add(*__pCargoBayObj);
	__drawer.add(*__pPulseCoreObj);
	__drawer.add(*__pWrenchObj);
	__drawer.add(*__pDroneObj);
	__drawer.add(*__pSpotLightObj);
	__drawer.add(*__pCharacterObj);


	// PostProcessor 초기화

	Material::setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);

	// __pPPPipeline->appendProcessor<MSAAPostProcessor>(true);
	__ppPipeline.appendProcessor<GammaCorrectionPostProcessor>(true);
	__ppPipeline.appendProcessor<BloomPostProcessor>();
	__pHDRPP = &__ppPipeline.appendProcessor<HDRPostProcessor>();


	// 렌더링 파이프라인 초기화

	__pRenderingPipeline = make_unique<LightPrePassRenderingPipeline>(
		__lightMgr, __camera, __drawer, __skybox, __ppPipeline);

	/*__pRenderingPipeline = make_unique<ForwardRenderingPipeline>(
		__lightMgr, __camera, __drawer, __skybox, __ppPipeline);*/
}

bool LightingTestScene::__keyFunc(const float deltaTime) noexcept
{
	const bool ESC = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
	if (ESC)
		return false;

	constexpr float MOVE_SPEED_FACTOR = .013f;
	const float MOVE_SPEED = (MOVE_SPEED_FACTOR * deltaTime);

	const bool
		LEFT = (GetAsyncKeyState('A') & 0x8000),
		RIGHT = (GetAsyncKeyState('D') & 0x8000),
		FRONT = (GetAsyncKeyState('W') & 0x8000),
		BACK = (GetAsyncKeyState('S') & 0x8000);

	Transform& cameraTransform = __camera.getTransform();
	Transform &characterTransform = __pCharacterObj->getTransform();

	AnimationManager &characterAnimMgr = __pCharacterObj->getAnimationManager();

	if (!(LEFT || RIGHT || FRONT || BACK))
	{
		characterAnimMgr.activateAnimation(__ANIM_IDX_LOOK_UP);
	}
	else
	{
		if (LEFT || RIGHT)
		{
			characterAnimMgr.activateAnimation(__ANIM_IDX_WALK_LEFT);
			Animation &leftWalkAnim = characterAnimMgr.getActiveAnimation();

			const vec4 &cameraHoriz = cameraTransform.getHorizontal();

			if (LEFT)
			{
				leftWalkAnim.setPlayingOrder(AnimationPlayingOrderType::FORWARD);

				const vec3 &posAdj = (cameraHoriz * -MOVE_SPEED);
				cameraTransform.adjustPosition(posAdj);
				characterTransform.adjustPosition(posAdj);
			}

			if (RIGHT)
			{
				leftWalkAnim.setPlayingOrder(AnimationPlayingOrderType::REVERSE);

				const vec3 &posAdj = (cameraHoriz * MOVE_SPEED);
				cameraTransform.adjustPosition(posAdj);
				characterTransform.adjustPosition(posAdj);
			}
		}

		if (FRONT || BACK)
		{
			characterAnimMgr.activateAnimation(__ANIM_IDX_WALK_FRONT);

			Animation &frontWalkAnim = characterAnimMgr.getActiveAnimation();

			const vec4 &cameraForward = cameraTransform.getForward();
			vec3 projForward = { cameraForward.x, 0.f, cameraForward.z };

			const float projForwardLength = length(projForward);
			if (projForwardLength > epsilon<float>())
			{
				projForward /= projForwardLength;

				if (FRONT)
				{
					frontWalkAnim.setPlayingOrder(AnimationPlayingOrderType::FORWARD);

					const vec3 &posAdj = (projForward * -MOVE_SPEED);
					cameraTransform.adjustPosition(posAdj);
					characterTransform.adjustPosition(posAdj);
				}

				if (BACK)
				{
					frontWalkAnim.setPlayingOrder(AnimationPlayingOrderType::REVERSE);

					const vec3 &posAdj = (projForward * MOVE_SPEED);
					cameraTransform.adjustPosition(posAdj);
					characterTransform.adjustPosition(posAdj);
				}
			}
		}
	}

	const bool
		KEY1 = (GetAsyncKeyState('1') & 0x8000),
		KEY2 = (GetAsyncKeyState('2') & 0x8000);

	if (KEY1)
		__pHDRPP->setExposure(__pHDRPP->getExposure() - .1f);

	if (KEY2)
		__pHDRPP->setExposure(__pHDRPP->getExposure() + .1f);

	return true;
}

void LightingTestScene::draw() noexcept
{
	__pRenderingPipeline->render();
	RenderContext::getCurrent()->requestBufferSwapping();
}

bool LightingTestScene::update(const float deltaTime) noexcept
{
	__blinkingDelay -= deltaTime;

	if (__blinkingDelay < epsilon<float>())
	{
		const float randVal = __randDistribute(__randEngine);
		__pCorridorObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, (randVal < .1f) ? .6f : 2.f);

		__blinkingDelay = 70.f;
	}

	__cargoBayEmissive += (deltaTime * .001f);
	__cargoBayEmissive = fmodf(__cargoBayEmissive, two_pi<float>());

	__droneEmissive += (deltaTime * .0001f);
	__droneEmissive = fmodf(__cargoBayEmissive, two_pi<float>());

	__pCargoBayObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 2.f * fabsf(cosf(__cargoBayEmissive)));
	__pDroneObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 3.f * fabsf(cosf(__droneEmissive)));

	__updater.process(&Updatable::update, deltaTime);
	__updated = true;

	return __keyFunc(deltaTime);
}

void LightingTestScene::onDisplay() noexcept
{
	if (!__updated)
		return;
	
	draw();
}

void LightingTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	__pRenderingPipeline->setScreenSize(width, height);
}

void LightingTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	Transform &cameraTransform = __camera.getTransform();
	Transform &characterTransform = __pCharacterObj->getTransform();

	const vec3 &cameraPos = cameraTransform.getPosition();
	const vec3 &characterPos = characterTransform.getPosition();

	const vec3 &rotationPivot = { characterPos.x, characterPos.y + 18.f, characterPos.z };

	cameraTransform.
		orbit(-(yDelta * ROTATION_SPEED), rotationPivot, cameraTransform.getHorizontal(), false).
		orbit(-(xDelta * ROTATION_SPEED), rotationPivot, { 0.f, 1.f, 0.f }, false);

	cameraTransform.
		rotateLocal(-(yDelta * ROTATION_SPEED), 0.f, 0.f).
		rotateGlobal(0.f, -(xDelta * ROTATION_SPEED), 0.f);

	characterTransform.rotateLocal(0.f, -(xDelta * ROTATION_SPEED), 0.f);
}

void LightingTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__camera.resetFov();
}

void LightingTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__camera.adjustFov(ZOOM_SPEED * zDelta);
}

bool LightingTestScene::onIdle(const float deltaTime) noexcept
{
	return update(deltaTime);
}