#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "RenderUnit.h"
#include "SimpleCamera.h"
#include "UniformBuffer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "LightDeployer.h"
#include "Updater.h"
#include "Drawer.h"
#include "CubeSkybox.h"

class LightTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<ObjectGL::UniformBuffer> __pUBLight;
	std::shared_ptr<ObjectGL::UniformBuffer> __pUBCamera;

	std::shared_ptr<Danburite::RenderingUnit> __pTerrainRU;
	std::shared_ptr<Danburite::RenderingUnit> __pNanosuitRU;
	std::shared_ptr<Danburite::RenderingUnit> __pLizardManRU;
	std::shared_ptr<Danburite::RenderingUnit> __pStreetLightRU;
	std::shared_ptr<Danburite::RenderingUnit> __pSkullRU;
	std::shared_ptr<Danburite::RenderingUnit> __pCubeRU;

	std::shared_ptr<Danburite::DirectionalLight> __pDirectionalLight;
	std::shared_ptr<Danburite::PointLight> __pStreetLight;
	std::shared_ptr<Danburite::SpotLight> __pRedSpotLight;
	std::shared_ptr<Danburite::SpotLight> __pGreenSpotLight;
	std::shared_ptr<Danburite::SpotLight> __pBlueSpotLight;
	std::shared_ptr<Danburite::PointLight> __pRotatingLight;

	std::shared_ptr<Danburite::SimpleCamera> __pCamera;

	std::shared_ptr<Danburite::CubeSkybox> __pSkybox;

	std::shared_ptr<Danburite::LightDeployer> __pLightDeployer;
	std::shared_ptr<Danburite::Updater> __pUpdater;
	std::shared_ptr<Danburite::Drawer> __pDrawer;

	void __keyFunc(const float deltaTime) noexcept;

public:
	LightTestScene();

	virtual void delta(const float deltaTime) noexcept override;
	virtual void update() noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual void onIdle(const float deltaTime) noexcept override;

	virtual ~LightTestScene() = default;
};
