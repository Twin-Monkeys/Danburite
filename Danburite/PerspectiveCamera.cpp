#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	PerspectiveCamera::PerspectiveCamera() noexcept
	{
		updateProjMatrix();
	}

	void PerspectiveCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		viewMatrix = __transform.getViewMatrix();
	}

	void PerspectiveCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}

	void PerspectiveCamera::_onDeploy(UniformSetter &uniformSetter) noexcept
	{
		Camera::_onDeploy(uniformSetter);
		uniformSetter.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __transform.getPosition());
	}
}