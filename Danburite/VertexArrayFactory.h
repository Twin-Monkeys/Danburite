#pragma once

#include "VertexArray.h"
#include "VertexAttributeFlag.h"
#include "VertexArrayFactoryException.h"

namespace Danburite
{
	class VertexArrayFactory abstract final
	{
	public:
		static std::shared_ptr<ObjectGL::VertexArray> createRectangle(
			const VertexAttributeFlag vertexFlag, const float edgeLength = 1.f);

		static std::shared_ptr<ObjectGL::VertexArray> createCircle(
			const VertexAttributeFlag vertexFlag, const float radius = 1.f, const size_t numSectors = 36ULL);

		static std::shared_ptr<ObjectGL::VertexArray> createCube(
			const VertexAttributeFlag vertexFlag, const float edgeLength = 1.f);

		static std::shared_ptr<ObjectGL::VertexArray> createSphere(
			const VertexAttributeFlag vertexFlag, const float radius = 1.f,
			const size_t numStacks = 18ULL, const size_t numSectors = 36ULL);

		static std::shared_ptr<ObjectGL::VertexArray> createTweakedTwinSphere(
			const VertexAttributeFlag vertexFlag, const float radius = 1.f,
			const size_t numStacks = 9ULL, const size_t numSectors = 18ULL);

		static std::shared_ptr<ObjectGL::VertexArray> createCylinder(
			const VertexAttributeFlag vertexFlag, const float topRadius = 1.f, const float bottomRadius = 1.f,
			const float height = 1.f, const size_t numSectors = 36ULL);
	};
}
