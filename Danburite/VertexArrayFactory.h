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
	};
}
