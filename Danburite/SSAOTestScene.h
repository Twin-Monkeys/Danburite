#pragma once

#include "Scene.h"
#include "ScreenEventHandler.h"
#include "SceneObject.h"
#include "PerspectiveCamera.h"
#include "LightManager.h"
#include "BatchProcessor.h"
#include "HDRPostProcessor.h"
#include "RenderingPipeline.h"

class SSAOTestScene : public Danburite::Scene, public ObjectGL::ScreenEventHandler
{
private:
	bool __updated = false;

	std::shared_ptr<Danburite::SceneObject> __pCubeObj;
	std::shared_ptr<Danburite::SceneObject> __pFloorObj;

	Danburite::PerspectiveCamera __camera;

	Danburite::LightManager __lightMgr;

	Danburite::BatchProcessor<Danburite::Updatable> __updater;
	Danburite::BatchProcessor<Danburite::SceneObject> __drawer;

	Danburite::HDRPostProcessor *__pHDRPP;
	std::unique_ptr<Danburite::RenderingPipeline> __pRenderingPipeline;

	bool __keyFunc(const float deltaTime) noexcept;

public:
	SSAOTestScene();

	virtual bool update(const float deltaTime) noexcept override;
	virtual void draw() noexcept override;

	virtual void onDisplay() noexcept override;
	virtual void onResize(const int width, const int height) noexcept override;
	virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept override;
	virtual void onMouseMButtonDown(const int x, const int y) noexcept override;
	virtual void onMouseWheel(const short zDelta) noexcept override;
	virtual bool onIdle(const float deltaTime) noexcept override;

	virtual ~SSAOTestScene() = default;
};