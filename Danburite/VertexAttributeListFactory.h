#pragma once

#include "VertexAttributeList.h"
#include "VertexAttributeType.h"
#include "Cache.h"

namespace Danburite
{
	class VertexAttributeListFactory abstract
	{
	private:
		class VertexAttributeListCache :
			public ObjectGL::Cache<VertexAttributeType, ObjectGL::VertexAttributeList>
		{
		protected:
			virtual ObjectGL::VertexAttributeList _onProvideValue(const VertexAttributeType &key) override;

		public:
			virtual ~VertexAttributeListCache() = default;
		};

	public:
		static const ObjectGL::VertexAttributeList &getInstance(const VertexAttributeType type) noexcept;
	};
}
