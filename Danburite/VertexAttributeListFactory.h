#pragma once

#include "VertexAttribute.h"
#include "VertexAttributeFlag.h"
#include "Cache.h"

namespace Danburite
{
	class VertexAttributeListFactory abstract
	{
	private:
		class VertexAttributeListCache :
			public ObjectGL::Cache<VertexAttributeFlag, std::vector<ObjectGL::VertexAttribute>>
		{
		protected:
			virtual std::vector<ObjectGL::VertexAttribute> _onProvideValue(const VertexAttributeFlag &key) override;

		public:
			virtual ~VertexAttributeListCache() = default;
		};

	public:
		static const std::vector<ObjectGL::VertexAttribute> &getInstance(const VertexAttributeFlag flag) noexcept;
	};
}
