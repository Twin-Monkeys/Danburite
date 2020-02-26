#include "GeometryTestScene.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderContext.h"
#include "AssetImporter.h"
#include <glm/gtx/rotate_vector.hpp>
#include "GLFunctionWrapper.h"
#include "VertexArrayFactory.h"
#include "TransparentPhongMaterial.h"
#include "TextureUtil.h"
#include "FrameBuffer.h"
#include "Constant.h"
#include <random>
#include "ReflectionMaterial.h"
#include "ReflectionPhongMaterial.h"
#include "RefractionMaterial.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

GeometryTestScene::GeometryTestScene()
{
	// ���� �ɼ�

	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	GLFunctionWrapper::setOption(GLOptionType::CULL_FACE, false);

	// Stencil mask ���� 0x00�� ��� Stencil Buffer clear bit�� 0�� �Ǿ� ���� Ŭ��� �ȵ�.
	// Depth mask�� ���� �����̴�. (Ŭ���� �� depth mask�� false�̸� Ŭ���� �ȵ�.)
	// GLFunctionWrapper::setStencilMask(0xFF); -> �⺻�̹Ƿ� �����ص� ����.

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program &explodingPhongProgram = programFactory.getProgram(ProgramType::EXPLODING_PHONG);


	//// Uniform Buffer ���� ////

	__pUBLight = make_shared<UniformBuffer>("UBLight", ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT);
	__pUBLight->registerProgram(explodingPhongProgram);

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(explodingPhongProgram);


	//// Rendering unit ���� ////

	RenderUnitManager &ruManager = RenderUnitManager::getInstance();

	__pCubeRU = AssetImporter::import(
		"res/asset/nanosuit/nanosuit.obj", Constant::Matrix::IDENTITY_MATRIX, MaterialType::EXPLODING_PHONG);

	__pCubeRU->getTransform().setScale(.5f);


	//// ���� ���� ////

	__pDirectionalLight = make_shared<DirectionalLight>(*__pUBLight);
	__pDirectionalLight->setDirection(1.f, -1.f, 0.f);
	__pDirectionalLight->setAlbedo(.8f, .8f, .8f);
	__pDirectionalLight->setDiffuseStrength(2.f);
	__pDirectionalLight->setSpecularStrength(2.f);


	//// ī�޶� ���� ////

	__pCamera = make_shared<SimpleCamera>();
	__pCamera->setPosition(0.f, 0.f, 25.f);

	__pUBCamera->addDeployable(__pCamera);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pCamera);


	//// Deployer / Updater �ʱ�ȭ ////

	__pUBCamera->addDeployable(__pCamera);

	__pLightDeployer = make_shared<LightDeployer>();
	__pLightDeployer->addLight(__pDirectionalLight);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pCubeRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pCubeRU);
}

bool GeometryTestScene::__keyFunc(const float deltaTime) noexcept
{
	const bool ESC = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
	if (ESC)
		return false;

	float accel = 1.f;
	const bool SHIFT = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
	if (SHIFT)
		accel *= 4.f;

	constexpr float MOVE_SPEED_FACTOR = .013f;
	const float MOVE_SPEED = (MOVE_SPEED_FACTOR * deltaTime * accel);

	const bool
		LEFT	= (GetAsyncKeyState('A') & 0x8000),
		RIGHT	= (GetAsyncKeyState('D') & 0x8000),
		FRONT	= (GetAsyncKeyState('W') & 0x8000),
		BACK	= (GetAsyncKeyState('S') & 0x8000),
		UP		= (GetAsyncKeyState('E') & 0x8000),
		DOWN	= (GetAsyncKeyState('Q') & 0x8000);

	if (LEFT)
		__pCamera->moveHorizontal(-MOVE_SPEED);
	
	if (RIGHT)
		__pCamera->moveHorizontal(MOVE_SPEED);

	if (FRONT)
		__pCamera->moveForward(MOVE_SPEED);

	if (BACK)
		__pCamera->moveForward(-MOVE_SPEED);

	if (UP)
		__pCamera->moveVertical(MOVE_SPEED);

	if (DOWN)
		__pCamera->moveVertical(-MOVE_SPEED);

	return true;
}

void GeometryTestScene::draw() noexcept
{
	__pUBCamera->batchDeploy();
	__pLightDeployer->batchDeploy();

	GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH_STENCIL);

	__pDrawer->batchDraw();

	RenderContext::getCurrent()->requestBufferSwapping();
}

bool GeometryTestScene::delta(const float deltaTime) noexcept
{
	if (!__keyFunc(deltaTime))
		return false;

	static float accum = 0.f;
	accum += deltaTime;

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program &explodingPhongProgram = programFactory.getProgram(ProgramType::EXPLODING_PHONG);
	explodingPhongProgram.setUniformFloat("displacementRatio", 5.f * (sinf(accum * .001f) + 1.f));

	return true;
}

void GeometryTestScene::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void GeometryTestScene::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void GeometryTestScene::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	glViewport(0, 0, width, height);
	__pCamera->setAspectRatio(width, height);
}

void GeometryTestScene::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	__pCamera->yaw(xDelta * ROTATION_SPEED);
	__pCamera->pitch(yDelta * ROTATION_SPEED);
}

void GeometryTestScene::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void GeometryTestScene::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

bool GeometryTestScene::onIdle(const float deltaTime) noexcept
{
	if (!delta(deltaTime))
		return false;

	update();
	return true;
}