#pragma once

#include "VertexArray.h"
#include "ShapeType.h"
#include "VertexAttributeFlag.h"
#include "VertexArrayFactoryException.h"

namespace Danburite
{
	class VertexArrayFactory abstract final
	{
	private:
		static std::shared_ptr<ObjectGL::VertexArray> __createInstance_rectangle(const VertexAttributeFlag vertexFlag);
		static std::shared_ptr<ObjectGL::VertexArray> __createInstance_cube(const VertexAttributeFlag vertexFlag);

	public:
		static std::shared_ptr<ObjectGL::VertexArray> createInstance(const ShapeType shapeType, const VertexAttributeFlag vertexFlag);
	};
}
