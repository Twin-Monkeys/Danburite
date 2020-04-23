#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "RenderUnit.h"
#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "LightHandler.h"
#include "Updater.h"
#include "Drawer.h"
#include "GammaCorrectionPostProcessor.h"
#include "MSAAPostProcessor.h"
#include "PostProcessingPipeline.h"

class HDRTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<Danburite::RenderUnit> __pBlubRU;
	std::shared_ptr<Danburite::RenderUnit> __pCargoBayRU;
	std::shared_ptr<Danburite::RenderUnit> __pPulseCoreRU;
	std::shared_ptr<Danburite::RenderUnit> __pDoorRU;
	std::shared_ptr<Danburite::RenderUnit> __pWallRU;

	std::shared_ptr<Danburite::PerspectiveCamera> __pCamera;

	std::shared_ptr<Danburite::PointLight> __pWhiteLight;

	std::shared_ptr<Danburite::LightHandler> __pLightHandler;
	std::shared_ptr<Danburite::Updater> __pUpdater;
	std::shared_ptr<Danburite::Drawer> __pDrawer;

	std::shared_ptr<Danburite::GammaCorrectionPostProcessor> __pGammaCorrectionPP;
	std::shared_ptr<Danburite::MSAAPostProcessor> __pMsaaPP;
	std::shared_ptr<Danburite::PostProcessingPipeline> __pPPPipeline;

	bool __keyFunc(const float deltaTime) noexcept;

public:
	HDRTestScene();

	virtual bool delta(const float deltaTime) noexcept override;
	virtual void update() noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual bool onIdle(const float deltaTime) noexcept override;

	virtual ~HDRTestScene() = default;
};