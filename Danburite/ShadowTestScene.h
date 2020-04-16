#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "RenderUnit.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "LightHandler.h"
#include "Updater.h"
#include "Drawer.h"
#include "GammaCorrectionPostProcessor.h"
#include "MSAAPostProcessor.h"
#include "PostProcessingPipeline.h"
#include "CubeSkybox.h"

class ShadowTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<Danburite::RenderUnit> __pNanosuitRU;
	std::shared_ptr<Danburite::RenderUnit> __pSkullRU;
	std::shared_ptr<Danburite::RenderUnit> __pRockSurroundRU;
	std::shared_ptr<Danburite::RenderUnit> __pChestRU;

	std::shared_ptr<Danburite::PerspectiveCamera> __pCamera;
	std::shared_ptr<Danburite::CubeSkybox> __pSkybox;

	std::shared_ptr<Danburite::PointLight> __pBlueLight;
	std::shared_ptr<Danburite::PointLight> __pWhiteLight;

	std::shared_ptr<Danburite::LightHandler> __pLightHandler;
	std::shared_ptr<Danburite::Updater> __pUpdater;
	std::shared_ptr<Danburite::Drawer> __pDrawer;

	std::shared_ptr<Danburite::GammaCorrectionPostProcessor> __pGammaCorrectionPP;
	std::shared_ptr<Danburite::MSAAPostProcessor> __pMsaaPP;
	std::shared_ptr<Danburite::PostProcessingPipeline> __pPPPipeline;

	bool __keyFunc(const float deltaTime) noexcept;

public:
	ShadowTestScene();

	virtual bool delta(const float deltaTime) noexcept override;
	virtual void update() noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual bool onIdle(const float deltaTime) noexcept override;

	virtual ~ShadowTestScene() = default;
};