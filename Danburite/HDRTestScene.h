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

	std::shared_ptr<Danburite::PerspectiveCamera> __pCamera;

	std::shared_ptr<Danburite::PointLight> __pBlueLight;
	std::shared_ptr<Danburite::PointLight> __pRedLight;

	std::shared_ptr<Danburite::LightHandler> __pLightHandler;
	std::shared_ptr<Danburite::Updater> __pUpdater;
	std::shared_ptr<Danburite::Drawer> __pDrawer;

	std::shared_ptr<Danburite::MSAAPostProcessor> __pMsaaPP;
	std::shared_ptr<Danburite::GammaCorrectionPostProcessor> __pGammaCorrectionPP;
	std::shared_ptr<Danburite::BloomPostProcessor> __pBloomPP;
	std::shared_ptr<Danburite::HDRPostProcessor> __pHDRPP;
	std::shared_ptr<Danburite::PostProcessingPipeline> __pPPPipeline;

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