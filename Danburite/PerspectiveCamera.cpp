#include "PerspectiveCamera.h"
#include <glm/gtx/rotate_vector.hpp>
#include "ShaderIdentifier.h"
#include <glm/gtx/quaternion.hpp>

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
		viewMatrix = toMat4(quat({ __pitch, __yaw, 0.f }));
		viewMatrix = translate(viewMatrix, -__pos);
	}

	void PerspectiveCamera::_onUpdateProjMatrix(mat4 &projMatrix) noexcept
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}

	void PerspectiveCamera::_onDeploy(UniformSetter &target) noexcept
	{
		Camera::_onDeploy(target);
		target.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __pos);
	}

	void PerspectiveCamera::pitch(const float angle) noexcept
	{
		__pitch -= angle;
	}

	void PerspectiveCamera::yaw(const float angle) noexcept
	{
		__yaw -= angle;
	}
}