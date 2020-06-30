#pragma once

#include <assimp/scene.h>
#include <glm/glm.hpp>

namespace Danburite
{
	class AssimpDataStructureConverter abstract final
	{
	public:
		static glm::mat4 toMat4(const aiMatrix4x4 &src) noexcept;
	};
}
