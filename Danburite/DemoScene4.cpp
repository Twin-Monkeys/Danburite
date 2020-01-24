#include "DemoScene4.h"
#include "ProgramFactory.h"
#include "VertexAttributeListFactory.h"
#include "RenderUnitManager.h"
#include "RenderingContext.h"
#include "AssetImporter.h"
#include "GLFunctionWrapper.h"
#include "VertexArrayFactory.h"
#include "Constant.h"
#include "MonoColorMaterial.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;
using namespace Danburite;

DemoScene4::DemoScene4()
{
	// 전역 옵션

	GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);

	// Stencil mask 값이 0x00인 경우 Stencil Buffer clear bit도 0이 되어 버퍼 클리어도 안됨.
	// Depth mask도 같은 원리이다. (클리어 전 depth mask가 false이면 클리어 안됨.)
	// GLFunctionWrapper::setStencilMask(0xFF); -> 기본이므로 생략해도 무방.

	ProgramFactory &programFactory = ProgramFactory::getInstance();
	Program &monoColorProgram = programFactory.getProgram(ProgramType::MONO_COLOR);


	//// Uniform Buffer 생성 ////

	__pUBCamera = make_shared<UniformBuffer>("UBCamera", ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA);
	__pUBCamera->registerProgram(monoColorProgram);


	//// Rendering unit 생성 ////

	RenderingUnitManager &ruManager = RenderingUnitManager::getInstance();
	VertexArrayFactory& vaFactory = VertexArrayFactory::getInstance();

	const shared_ptr<VertexArray>& pCubeVA =
		vaFactory.getVertexArray(ShapeType::CUBE, VertexAttributeType::POS3_COLOR4);

	const shared_ptr<MonoColorMaterial>& pCubeMaterial =
		make_shared<MonoColorMaterial>(VertexAttributeType::POS3_COLOR4);

	pCubeMaterial->setColor({ 0.f, 1.f, 0.f, 1.f });

	unique_ptr<Mesh> pMesh = make_unique<Mesh>(pCubeVA, pCubeMaterial);
	__pCubeRU = ruManager.createRenderingUnit(move(pMesh));


	//// 카메라 생성 ////

	__pCamera = make_shared<SimpleCamera>();
	__pCamera->setPosition(10.f, 10.f, 10.f);
	__pCamera->pitch(-quarter_pi<float>() * .7f);
	__pCamera->yaw(quarter_pi<float>());

	__pUBCamera->addDeployable(__pCamera);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pCamera);


	//// Deployer / Updater 초기화 ////

	__pUBCamera->addDeployable(__pCamera);

	__pUpdater = make_shared<Updater>();
	__pUpdater->addUpdatable(__pCubeRU);
	__pUpdater->addUpdatable(__pCamera);

	__pDrawer = make_shared<Drawer>();
	__pDrawer->addDrawable(__pCubeRU);
}

void DemoScene4::__keyFunc(const float deltaTime) noexcept
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

void DemoScene4::draw() noexcept
{
	__pUBCamera->batchDeploy();

	GLFunctionWrapper::clearBuffers(FrameBufferClearFlag::COLOR_DEPTH_STENCIL);

	__pDrawer->batchDraw();

	RenderingContext::requestBufferSwapping();
}

void DemoScene4::delta(const float deltaTime) noexcept
{
	__keyFunc(deltaTime);
}

void DemoScene4::update() noexcept
{
	__pUpdater->batchUpdate();
	__updated = true;
}

void DemoScene4::onDisplay() noexcept
{
	if (__updated)
		draw();
}

void DemoScene4::onResize(const int width, const int height) noexcept
{
	if (!width || !height)
		return;

	glViewport(0, 0, width, height);
	__pCamera->setAspectRatio(width, height);
}

void DemoScene4::onMouseDelta(const int xDelta, const int yDelta) noexcept
{
	constexpr float ROTATION_SPEED = .004f;

	__pCamera->yaw(xDelta * ROTATION_SPEED);
	__pCamera->pitch(yDelta * ROTATION_SPEED);
}

void DemoScene4::onMouseMButtonDown(const int x, const int y) noexcept
{
	__pCamera->resetFov();
}

void DemoScene4::onMouseWheel(const short zDelta) noexcept
{
	constexpr float ZOOM_SPEED = -.0005f;

	__pCamera->adjustFov(ZOOM_SPEED * zDelta);
}

void DemoScene4::onIdle(const float deltaTime) noexcept
{
	delta(deltaTime);
	update();
}