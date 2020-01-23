#pragma once

#include "VertexAttribute.h"
#include "VertexAttributeDescriptorType.h"
#include "Cache.h"
#include "AssertException.h"

namespace Danburite
{
	class VertexAttributeDescriptorFactory abstract
	{
	private:
		class VertexAttributeDescriptorCache :
			public ObjectGL::Cache<VertexAttributeDescriptorType, ObjectGL::VertexAttributeDescriptor>
		{
		protected:
			virtual ObjectGL::VertexAttributeDescriptor _onProvideValue(const VertexAttributeDescriptorType &key) override;

		public:
			virtual ~VertexAttributeDescriptorCache() = default;
		};

	public:
		static const ObjectGL::VertexAttributeDescriptor &getInstance(const VertexAttributeDescriptorType type) noexcept;
	};
}