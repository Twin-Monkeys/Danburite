#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "RenderUnit.h"
#include "PerspectiveCamera.h"
#include "UniformBuffer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "LightDeployer.h"
#include "Updater.h"
#include "Drawer.h"
#include "CubeSkybox.h"
#include "MSAAPostProcessor.h"

class MSAATestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<ObjectGL::UniformBuffer> __pUBMaterial;
	std::shared_ptr<ObjectGL::UniformBuffer> __pUBCamera;

	std::shared_ptr<Danburite::RenderUnit> __pCubeRU;
	std::shared_ptr<Danburite::PerspectiveCamera> __pCamera;

	std::shared_ptr<Danburite::Updater> __pUpdater;
	std::shared_ptr<Danburite::Drawer> __pDrawer;

	std::shared_ptr<Danburite::MSAAPostProcessor> __pMSAAPP;

	bool __keyFunc(const float deltaTime) noexcept;

public:
	MSAATestScene();

	virtual bool delta(const float deltaTime) noexcept override;
	virtual void update() noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual bool onIdle(const float deltaTime) noexcept override;

	virtual ~MSAATestScene() = default;
};