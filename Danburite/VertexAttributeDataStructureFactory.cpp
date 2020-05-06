#include "VertexAttributeDataStructureFactory.h"
#include <cassert>

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	const VertexAttributeDataStructure &
		VertexAttributeDataStructureFactory::getInstance(const VertexAttributeDataStructureType type) noexcept
	{
		static VertexAttributeDescriptorCache vertexAttribDescCache;
		return vertexAttribDescCache.getValue(type);
	}

	VertexAttributeDataStructure
		VertexAttributeDataStructureFactory::
		VertexAttributeDescriptorCache::_onProvideValue(const VertexAttributeDataStructureType &key)
	{
		switch (key)
		{
		case VertexAttributeDataStructureType::VEC2:
			return { 2, ElementType::FLOAT };

		case VertexAttributeDataStructureType::VEC3:
			return { 3, ElementType::FLOAT };

		case VertexAttributeDataStructureType::VEC4:
			return { 4, ElementType::FLOAT };

		case VertexAttributeDataStructureType::UVEC4:
			return { 4, ElementType::UNSIGNED_INT };
		}

		assert(false);
		return { 2, ElementType::FLOAT };
	}
}