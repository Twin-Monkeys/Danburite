#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "SceneObject.h"
#include "PerspectiveCamera.h"
#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "BatchProcessor.h"
#include "HDRPostProcessor.h"
#include "PostProcessingPipeline.h"
#include "RenderingPipeline.h"
#include <random>

class LightingTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<Danburite::SceneObject> __pCorridorObj;
	std::shared_ptr<Danburite::SceneObject> __pCargoBayObj;
	std::shared_ptr<Danburite::SceneObject> __pPulseCoreObj;
	std::shared_ptr<Danburite::SceneObject> __pDoorObj;
	std::shared_ptr<Danburite::SceneObject> __pWrenchObj;
	std::shared_ptr<Danburite::SceneObject> __pDroneObj;
	std::shared_ptr<Danburite::SceneObject> __pHoverDroneObj;
	std::shared_ptr<Danburite::SceneObject> __pHoverBikeObj;
	std::shared_ptr<Danburite::SceneObject> __pSpotLightObj;
	std::shared_ptr<Danburite::SceneObject> __pCharacterObj;

	Danburite::PerspectiveCamera __camera;

	Danburite::LightManager __lightMgr;
	Danburite::SpotLight *__pSpotLight1 = nullptr;
	Danburite::SpotLight *__pSpotLight2 = nullptr;

	Danburite::BatchProcessor<Danburite::Updatable> __updater;
	Danburite::BatchProcessor<Danburite::Drawable> __drawer;

	Danburite::Skybox __skybox;
	Danburite::HDRPostProcessor *__pHDRPP;
	Danburite::PostProcessingPipeline __ppPipeline;

	std::unique_ptr<Danburite::RenderingPipeline> __pRenderingPipeline;

	std::default_random_engine __randEngine;
	std::uniform_real_distribution<float> __randDistribute;

	std::uniform_real_distribution<float> __posDistributeX { -18.f, 18.f };
	std::uniform_real_distribution<float> __posDistributeZ { 120.f, 205.f };

	float __blinkingDelay = 0.f;
	float __cargoBayEmissive = 0.f;

	bool __doorOpened = false;
	bool __mButtonDown = false;

	static constexpr size_t __NUM_DRONES = 100ULL;
	static constexpr size_t __NUM_SMALL_LIGHTS = 70ULL;

	static constexpr size_t __ANIM_IDX_LOOK_UP = 3ULL;
	static constexpr size_t __ANIM_IDX_RUN_FRONT = 4ULL;
	static constexpr size_t __ANIM_IDX_WALK_CRAWL = 6ULL;
	static constexpr size_t __ANIM_IDX_WALK_FRONT = 8ULL;
	static constexpr size_t __ANIM_IDX_WALK_LEFT = 9ULL;

	static constexpr float __CHARACTER_DIST_Y = 28.f;
	static constexpr float __CHARACTER_DIST_Z = 30.f;

	bool __keyFunc(const float deltaTime) noexcept;

public:
	LightingTestScene();

	virtual bool update(const float deltaTime) noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseMButtonUp(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual bool onIdle(const float deltaTime) noexcept override;

	virtual ~LightingTestScene() = default;
};