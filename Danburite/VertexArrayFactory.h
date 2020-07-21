#pragma once

#include "VertexArray.h"
#include "VertexAttributeFlag.h"
#include "VertexArrayFactoryException.h"

namespace Danburite
{
	class VertexArrayFactory abstract final
	{
	public:
		static std::shared_ptr<ObjectGL::VertexArray> createRectangle(const VertexAttributeFlag vertexFlag);
		static std::shared_ptr<ObjectGL::VertexArray> createCube(const VertexAttributeFlag vertexFlag);

		static std::shared_ptr<ObjectGL::VertexArray> createSphere(
			const VertexAttributeFlag vertexFlag, const size_t numStacks = 18ULL, const size_t numSectors = 36ULL);
	};
}
