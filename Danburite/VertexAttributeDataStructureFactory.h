#pragma once

#include "VertexAttribute.h"
#include "VertexAttributeDataStructureType.h"
#include "Cache.h"

namespace Danburite
{
	class VertexAttributeDataStructureFactory abstract
	{
	private:
		class VertexAttributeDescriptorCache :
			public ObjectGL::Cache<VertexAttributeDataStructureType, ObjectGL::VertexAttributeDataStructure>
		{
		protected:
			virtual ObjectGL::VertexAttributeDataStructure _onProvideValue(const VertexAttributeDataStructureType &key) override;

		public:
			virtual ~VertexAttributeDescriptorCache() = default;
		};

	public:
		static const ObjectGL::VertexAttributeDataStructure &getInstance(const VertexAttributeDataStructureType type) noexcept;
	};
}