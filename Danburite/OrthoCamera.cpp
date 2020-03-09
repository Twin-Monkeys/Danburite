#include "OrthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void OrthoCamera::_onUpdateViewMatrix(mat4 &viewMatrix) noexcept
	{
		viewMatrix = __transform.getViewMatrix();
	}

	void OrthoCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = ortho(__xLeft, __xRight, __yBottom, __yTop, __zNear, __zFar);
	}

	void OrthoCamera::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		Camera::_onDeploy(uniformSetter);
		uniformSetter.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __transform.getPosition());
	}
}