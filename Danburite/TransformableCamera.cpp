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
		viewMatrix = inverse(__transform.getMatrix());
	}

	void TransformableCamera::_onDeploy(UniformSetter &cameraSetter) noexcept
	{
		cameraSetter.setUniformVec3(
			ShaderIdentifier::Name::Camera::POSITION, __transform.getPosition());
	}
}