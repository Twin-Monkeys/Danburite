#pragma once

#include "VertexArray.h"
#include "ShapeType.h"
#include "VertexAttributeType.h"
#include "Cache.h"
#include "RenderContext.h"

namespace Danburite
{
	class VertexArrayFactory : public ObjectGL::RenderContextListener<VertexArrayFactory>
	{
		friend ObjectGL::RenderContextListener<VertexArrayFactory>;

	private:
		class RectangleCache : public ObjectGL::Cache<VertexAttributeType, std::shared_ptr<ObjectGL::VertexArray>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::VertexArray> _onProvideValue(const VertexAttributeType &key) override;
		};

		class CubeCache : public ObjectGL::Cache<VertexAttributeType, std::shared_ptr<ObjectGL::VertexArray>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::VertexArray> _onProvideValue(const VertexAttributeType &key) override;
		};

		class CacheCache : public ObjectGL::Cache<ShapeType, std::shared_ptr<ObjectGL::Cache<VertexAttributeType, std::shared_ptr<ObjectGL::VertexArray>>>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::Cache<VertexAttributeType, std::shared_ptr<ObjectGL::VertexArray>>>
				_onProvideValue(const ShapeType &key) override;
		};

		CacheCache __cacheCache;

		VertexArrayFactory() = default;
		VertexArrayFactory(const VertexArrayFactory &) = delete;
		VertexArrayFactory(VertexArrayFactory &&) = delete;

	public:
		std::shared_ptr<ObjectGL::VertexArray>
			getVertexArray(const ShapeType shapeType, const VertexAttributeType vertexType);
	};
}
