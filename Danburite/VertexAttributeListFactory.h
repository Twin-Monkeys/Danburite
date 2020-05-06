#pragma once

#include "VertexAttribute.h"
#include "VertexAttributeType.h"
#include "Cache.h"

namespace Danburite
{
	class VertexAttributeListFactory abstract
	{
	private:
		class VertexAttributeListCache :
			public ObjectGL::Cache<VertexAttributeType, std::vector<ObjectGL::VertexAttribute>>
		{
		protected:
			virtual std::vector<ObjectGL::VertexAttribute> _onProvideValue(const VertexAttributeType &key) override;

		public:
			virtual ~VertexAttributeListCache() = default;
		};

	public:
		static const std::vector<ObjectGL::VertexAttribute> &getInstance(const VertexAttributeType type) noexcept;
	};
}
