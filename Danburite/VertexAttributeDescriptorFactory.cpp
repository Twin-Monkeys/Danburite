#include "VertexAttributeDescriptorFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	const VertexAttributeDescriptor &
		VertexAttributeDescriptorFactory::getInstance(const VertexAttributeDescriptorType type) noexcept
	{
		static VertexAttributeDescriptorCache vertexAttribDescCache;

		return vertexAttribDescCache.getValue(type);
	}

	VertexAttributeDescriptor
		VertexAttributeDescriptorFactory::
		VertexAttributeDescriptorCache::_onProvideValue(const VertexAttributeDescriptorType &key)
	{
		switch (key)
		{
		case VertexAttributeDescriptorType::VEC2:
			return { 2, ElementType::FLOAT };

		case VertexAttributeDescriptorType::VEC3:
			return { 3, ElementType::FLOAT };

		case VertexAttributeDescriptorType::VEC4:
			return { 4, ElementType::FLOAT };
		}

		throw AssertException();
	}
}