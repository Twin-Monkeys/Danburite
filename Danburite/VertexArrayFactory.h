#pragma once

#include "VertexArray.h"
#include "ShapeType.h"
#include "VertexAttributeFlag.h"
#include "Cache.h"
#include "RenderContext.h"

namespace Danburite
{
	class VertexArrayFactory : public ObjectGL::ContextDependentSingleton<VertexArrayFactory>
	{
		friend ObjectGL::ContextDependentSingleton<VertexArrayFactory>;

	private:
		class RectangleCache : public ObjectGL::Cache<VertexAttributeFlag, std::shared_ptr<ObjectGL::VertexArray>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::VertexArray> _onProvideValue(const VertexAttributeFlag&key) override;
		};

		class CubeCache : public ObjectGL::Cache<VertexAttributeFlag, std::shared_ptr<ObjectGL::VertexArray>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::VertexArray> _onProvideValue(const VertexAttributeFlag&key) override;
		};

		class CacheCache : public ObjectGL::Cache<ShapeType, std::shared_ptr<ObjectGL::Cache<VertexAttributeFlag, std::shared_ptr<ObjectGL::VertexArray>>>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::Cache<VertexAttributeFlag, std::shared_ptr<ObjectGL::VertexArray>>>
				_onProvideValue(const ShapeType &key) override;
		};

		CacheCache __cacheCache;

		VertexArrayFactory() = default;
		VertexArrayFactory(const VertexArrayFactory &) = delete;
		VertexArrayFactory(VertexArrayFactory &&) = delete;

	public:
		std::shared_ptr<ObjectGL::VertexArray>
			getVertexArrayPtr(const ShapeType shapeType, const VertexAttributeFlag vertexFlag);

		ObjectGL::VertexArray &
			getVertexArrayReference(const ShapeType shapeType, const VertexAttributeFlag vertexFlag);
	};
}
