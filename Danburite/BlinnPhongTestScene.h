#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "RenderUnit.h"
#include "SimpleCamera.h"
#include "UniformBuffer.h"
#include "PointLight.h"
#include "LightDeployer.h"
#include "Updater.h"
#include "Drawer.h"
#include "GammaCorrectionPostProcessor.h"

class BlinnPhongTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<ObjectGL::UniformBuffer> __pUBLight;
	std::shared_ptr<ObjectGL::UniformBuffer> __pUBCamera;
	std::shared_ptr<ObjectGL::UniformBuffer> __pUBGammaCorrection;

	std::shared_ptr<Danburite::RenderingUnit> __pFloorRU;
	std::shared_ptr<Danburite::SimpleCamera> __pCamera;

	std::array<std::shared_ptr<Danburite::PointLight>, 4> __arrPointLight;

	std::shared_ptr<Danburite::LightDeployer> __pLightDeployer;
	std::shared_ptr<Danburite::Updater> __pUpdater;
	std::shared_ptr<Danburite::Drawer> __pDrawer;

	std::shared_ptr<Danburite::GammaCorrectionPostProcessor> __pGammaCorrectionPP;

	void __keyFunc(const float deltaTime) noexcept;

public:
	BlinnPhongTestScene();

	virtual void delta(const float deltaTime) noexcept override;
	virtual void update() noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual void onIdle(const float deltaTime) noexcept override;

	virtual ~BlinnPhongTestScene() = default;
};