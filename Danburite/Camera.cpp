#include "Camera.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void Camera::update(const float deltaTime) noexcept
	{
		_onUpdateViewMatrix(__viewMat);
		_onUpdateProjMatrix(__projMat);
	}

	void Camera::selfDeploy() noexcept
	{
		CameraUniformInterface &cameraUI = __cameraUB.getInterface();

		cameraUI.viewMat = __viewMat;
		cameraUI.projMat = __projMat;
		_onDeploy(cameraUI);

		__cameraUB.selfDeploy();
	}
}