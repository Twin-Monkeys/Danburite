#include "TransformableCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void TransformableCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		__transform.updateMatrix();

		const vec3 &position = __transform.getPosition();
		const vec3 &forward = __transform.getForward();
		const vec3 &up = __transform.getVertical();
		
		viewMatrix = glm::lookAt(position, position + forward, up);
	}

	void TransformableCamera::_onDeploy(CameraUniformInterface &cameraUI) noexcept
	{
		cameraUI.pos = __transform.getPosition();
	}
}