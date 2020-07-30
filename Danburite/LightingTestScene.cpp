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

	__pGlobalLight = &__lightMgr.createLight<DirectionalLight>();
	__pGlobalLight->setAlbedo(1.f, 1.f, 1.f);
	__pGlobalLight->setAmbientStrength(.002f);
	__pGlobalLight->setDiffuseStrength(0.f);
	__pGlobalLight->setSpecularStrength(0.f);
	__pGlobalLight->setShadowEnabled(false);

	__pPointLight = &__lightMgr.createLight<PointLight>();
	__pPointLight->setAlbedo(.25f, .35f, .8f);
	__pPointLight->setAmbientStrength(.1f);
	__pPointLight->setDiffuseStrength(20.f);
	__pPointLight->setSpecularStrength(20.f);
	__pPointLight->setAttenuation(1.f, .35f, .44f);
	__pPointLight->setShadowEnabled(true);

	Transform &pointLightTransform = __pPointLight->getTransform();
	pointLightTransform.setPosition(8.f, 5.f, 110.f);


	//// Updater / Drawer 초기화 ////

	__updater.add(__camera);
	__updater.add(*__pGlobalLight);
	__updater.add(*__pPointLight);
	__updater.add(*__pCorridorObj);
	__updater.add(*__pCargoBayObj);
	__updater.add(*__pPulseCoreObj);
	__updater.add(*__pWrenchObj);
	__updater.add(*__pCharacterObj);

	__drawer.add(*__pCorridorObj);
	__drawer.add(*__pCargoBayObj);
	__drawer.add(*__pPulseCoreObj);
	__drawer.add(*__pWrenchObj);
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
		if (LEFT)
		{
			characterAnimMgr.activateAnimation(__ANIM_IDX_WALK_LEFT);

			Animation &leftWalkAnim = characterAnimMgr.getActiveAnimation();
			leftWalkAnim.setPlayingOrder(AnimationPlayingOrderType::FORWARD);

			cameraTransform.moveHorizontal(-MOVE_SPEED);
			characterTransform.moveHorizontal(MOVE_SPEED);
		}

		if (RIGHT)
		{
			characterAnimMgr.activateAnimation(__ANIM_IDX_WALK_LEFT);

			Animation &leftWalkAnim = characterAnimMgr.getActiveAnimation();
			leftWalkAnim.setPlayingOrder(AnimationPlayingOrderType::REVERSE);

			cameraTransform.moveHorizontal(MOVE_SPEED);
			characterTransform.moveHorizontal(-MOVE_SPEED);
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
					cameraTransform.adjustPosition(projForward * -MOVE_SPEED);
					characterTransform.adjustPosition(projForward * -MOVE_SPEED);
				}

				if (BACK)
				{
					frontWalkAnim.setPlayingOrder(AnimationPlayingOrderType::REVERSE);
					cameraTransform.adjustPosition(projForward * MOVE_SPEED);
					characterTransform.adjustPosition(projForward * MOVE_SPEED);
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
		__pCorridorObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, (randVal < .1f) ? .2f : 1.f);

		__blinkingDelay = 70.f;
	}

	__cargoBayEmissive += (deltaTime * .001f);
	__cargoBayEmissive = fmodf(__cargoBayEmissive, two_pi<float>());
	__pCargoBayObj->traverseMaterial<PhongMaterial>(&PhongMaterial::setEmissiveStrength, 2.f * fabsf(cosf(__cargoBayEmissive)));

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
		orbit(-(yDelta * ROTATION_SPEED), rotationPivot, cameraTransform.getHorizontal()).
		orbit(-(xDelta * ROTATION_SPEED), rotationPivot, { 0.f, 1.f, 0.f });

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