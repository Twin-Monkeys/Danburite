#include "VertexAttributeListFactory.h"
#include "VertexAttributeDataStructureFactory.h"
#include "ShaderIdentifier.h"
#include <cassert>

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	const std::vector<VertexAttribute> &VertexAttributeListFactory::getInstance(const VertexAttributeFlag type) noexcept
	{
		static VertexAttributeListCache vertexAttribListCache;
		return vertexAttribListCache.getValue(type);
	}

	std::vector<VertexAttribute> VertexAttributeListFactory::
		VertexAttributeListCache::_onProvideValue(const VertexAttributeFlag &key)
	{
		vector<VertexAttribute> retVal;

		const VertexAttributeDataStructure &VEC2 =
			VertexAttributeDataStructureFactory::getInstance(VertexAttributeDataStructureType::VEC2);

		const VertexAttributeDataStructure &VEC3 =
			VertexAttributeDataStructureFactory::getInstance(VertexAttributeDataStructureType::VEC3);

		const VertexAttributeDataStructure &VEC4 =
			VertexAttributeDataStructureFactory::getInstance(VertexAttributeDataStructureType::VEC4);

		GLsizei offset = 0;
		if (key & VertexAttributeFlag::POS3)
		{
			retVal.emplace_back(
				ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, 0, offset);

			offset += VEC3.memSize();
		}

		if (key & VertexAttributeFlag::COLOR4)
		{
			retVal.emplace_back(
				ShaderIdentifier::Value::VertexAttribute::COLOR_LOCATION, VEC4, 0, offset);

			offset += VEC4.memSize();
		}

		if (key & VertexAttributeFlag::NORMAL3)
		{
			retVal.emplace_back(
				ShaderIdentifier::Value::VertexAttribute::NORMAL_LOCATION, VEC3, 0, offset);

			offset += VEC3.memSize();
		}

		if (key & VertexAttributeFlag::TEXCOORD2)
		{
			retVal.emplace_back(
				ShaderIdentifier::Value::VertexAttribute::TEX_COORD_LOCATION, VEC2, 0, offset);

			offset += VEC2.memSize();
		}

		if (key & VertexAttributeFlag::TANGENT3)
		{
			retVal.emplace_back(
				ShaderIdentifier::Value::VertexAttribute::TANGENT_LOCATION, VEC3, 0, offset);

			offset += VEC3.memSize();
		}

		if (key & VertexAttributeFlag::MODELMAT16)
		{
			for (GLuint i = 0U; i < 4U; i++)
			{
				retVal.emplace_back(
					ShaderIdentifier::Value::VertexAttribute::MODEL_MATRIX_LOCATION + i, VEC4, 0, offset, 1);

				offset += VEC4.memSize();
			}
		}

		for (VertexAttribute &attrib : retVal)
			attrib.stride = offset;

		return retVal;
	}
}