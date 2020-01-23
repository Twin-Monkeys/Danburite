#include "DemoScene3.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderingContext.h"
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

DemoScene3::DemoScene3()
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

	RenderingUnitManager &ruManager = RenderingUnitManager::getInstance();

	__pNanosuitRU = AssetImporter::import(
		"res/asset/nanosuit/nanosuit.obj", Constant::Matrix::IDENTITY_MATRIX, MaterialType::EXPLODING_PHONG);

	__pNanosuitRU->getTransform().setScale(.5f);


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
	__pUpdater->addUpdatable(__pNanosuitRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pNanosuitRU);
}

void DemoScene3::__keyFunc(const float deltaTime) noexcept
{
	const bool ESC = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
	if (ESC)
		RenderingContext::requestScreenClose();

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
}

void DemoScene3::draw() noexcept
{
	__pUBCamera->batchDeploy();
	__pLightDeployer->batchDeploy();

	GLFunctionWrapper::clearBuffers(FrameBufferClearFlag::COLOR_DEPTH_STENCIL);

	__pDrawer->batchDraw();

	RenderingContext::requestBufferSwapping();
}

void DemoScene3::delta(const float deltaTime) noexcept
{
	__keyFunc(deltaTime);

	static float accum = 0.f;
	accum += deltaTime;

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program &explodingPhongProgram = programFactory.getProgram(ProgramType::EXPLODING_PHONG);
	explodingPhongProgram.setUniformFloat("displacementRatio", 5.f * (sinf(accum * .001f) + 1.f));
}

void DemoScene3::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void DemoScene3::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void DemoScene3::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	glViewport(0, 0, width, height);
	__pCamera->setAspectRatio(width, height);
}

void DemoScene3::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	__pCamera->yaw(xDelta * ROTATION_SPEED);
	__pCamera->pitch(yDelta * ROTATION_SPEED);
}

void DemoScene3::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void DemoScene3::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

void DemoScene3::onIdle(const float deltaTime) noexcept
{
	delta(deltaTime);
	update();
}