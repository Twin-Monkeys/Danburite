#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "SceneObject.h"
#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "LightHandler.h"
#include "Updater.h"
#include "Drawer.h"
#include "MSAAPostProcessor.h"
#include "GammaCorrectionPostProcessor.h"
#include "BloomPostProcessor.h"
#include "HDRPostProcessor.h"
#include "PostProcessingPipeline.h"
#include "RenderingPipeline.h"

class HDRTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<Danburite::SceneObject> __pFloorObj;
	std::shared_ptr<Danburite::SceneObject> __pLampObj;
	std::shared_ptr<Danburite::SceneObject> __pCargoBayObj;
	std::shared_ptr<Danburite::SceneObject> __pPulseCoreObj;
	std::shared_ptr<Danburite::SceneObject> __pDoorObj;
	std::shared_ptr<Danburite::SceneObject> __pLizardObj;
	std::shared_ptr<Danburite::SceneObject> __pGirlObj;
	std::shared_ptr<Danburite::SceneObject> __pSphereObj;

	std::shared_ptr<Danburite::PerspectiveCamera> __pCamera;

	std::shared_ptr<Danburite::PointLight> __pBlueLight;
	std::shared_ptr<Danburite::PointLight> __pRedLight;

	std::shared_ptr<Danburite::LightHandler> __pLightHandler;
	Danburite::Updater __updater;
	Danburite::Drawer __drawer;

	Danburite::HDRPostProcessor *__pHDRPP;
	std::shared_ptr<Danburite::PostProcessingPipeline> __pPPPipeline;

	std::unique_ptr<Danburite::RenderingPipeline> __pRenderingPipeline;

	float __emissiveStrength = 0.f;
	bool __doorOpened = false;

	bool __keyFunc(const float deltaTime) noexcept;

public:
	HDRTestScene();

	virtual bool update(const float deltaTime) noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual bool onIdle(const float deltaTime) noexcept override;

	virtual ~HDRTestScene() = default;
};