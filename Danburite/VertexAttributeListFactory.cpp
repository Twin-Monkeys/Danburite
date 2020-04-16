#include "VertexAttributeListFactory.h"
#include "VertexAttributeDescriptorFactory.h"
#include "ShaderIdentifier.h"
#include <cassert>

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	const VertexAttributeList& VertexAttributeListFactory::getInstance(const VertexAttributeType type) noexcept
	{
		static VertexAttributeListCache vertexAttribListCache;
		return vertexAttribListCache.getValue(type);
	}

	VertexAttributeList VertexAttributeListFactory::VertexAttributeListCache::_onProvideValue(const VertexAttributeType &key)
	{
		VertexAttributeList retVal;

		const VertexAttributeDescriptor &VEC2 =
			VertexAttributeDescriptorFactory::getInstance(VertexAttributeDescriptorType::VEC2);

		const VertexAttributeDescriptor &VEC3 =
			VertexAttributeDescriptorFactory::getInstance(VertexAttributeDescriptorType::VEC3);

		const VertexAttributeDescriptor &VEC4 =
			VertexAttributeDescriptorFactory::getInstance(VertexAttributeDescriptorType::VEC4);

		switch (key)
		{
		case VertexAttributeType::POS3:
			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, VEC3.memSize(), 0);
			break;

		case VertexAttributeType::POS3_COLOR4:
		{
			const GLsizei STRIDE = (VEC3.memSize() + VEC4.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::COLOR_LOCATION, VEC4, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_NORMAL3:
		{
			const GLsizei STRIDE = (VEC3.memSize() * 2);
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::NORMAL_LOCATION, VEC3, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_COLOR4_NORMAL3:
		{
			const GLsizei STRIDE = (VEC3.memSize() + VEC4.memSize() + VEC3.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::COLOR_LOCATION, VEC4, STRIDE, offset);
			offset += VEC4.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::NORMAL_LOCATION, VEC3, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_TEXCOORD2:
		{
			const GLsizei STRIDE = (VEC3.memSize() + VEC2.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::TEX_COORD_LOCATION, VEC2, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_COLOR4_TEXCOORD2:
		{
			const GLsizei STRIDE = (VEC3.memSize() + VEC4.memSize() + VEC2.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::COLOR_LOCATION, VEC4, STRIDE, offset);
			offset += VEC4.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::TEX_COORD_LOCATION, VEC2, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_NORMAL3_TEXCOORD2:
		{
			const GLsizei STRIDE = ((VEC3.memSize() * 2) + VEC2.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::NORMAL_LOCATION, VEC3, STRIDE, offset);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::TEX_COORD_LOCATION, VEC2, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_COLOR4_NORMAL3_TEXCOORD2:
		{
			const GLsizei STRIDE = (VEC3.memSize() + VEC4.memSize() + VEC3.memSize() + VEC2.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::COLOR_LOCATION, VEC4, STRIDE, offset);
			offset += VEC4.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::NORMAL_LOCATION, VEC3, STRIDE, offset);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::TEX_COORD_LOCATION, VEC2, STRIDE, offset);
		}
			break;

		case VertexAttributeType::POS3_NORMAL3_TEXCOORD2_TANGENT3:
		{
			const GLsizei STRIDE = (VEC3.memSize() + VEC3.memSize() + VEC2.memSize() + VEC3.memSize());
			GLsizei offset = 0;

			retVal.add(ShaderIdentifier::Value::VertexAttribute::POSITION_LOCATION, VEC3, STRIDE, 0);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::NORMAL_LOCATION, VEC3, STRIDE, offset);
			offset += VEC3.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::TEX_COORD_LOCATION, VEC2, STRIDE, offset);
			offset += VEC2.memSize();

			retVal.add(ShaderIdentifier::Value::VertexAttribute::TANGENT_LOCATION, VEC3, STRIDE, offset);
		}
		break;

		case VertexAttributeType::MODELMAT16:
		{
			const GLsizei STRIDE = (4 * VEC4.memSize());
			GLsizei offset = 0;

			for (GLuint i = 0U; i < 4U; i++)
			{
				retVal.add(ShaderIdentifier::Value::VertexAttribute::MODEL_MATRIX_LOCATION + i, VEC4, STRIDE, offset, 1);
				offset += VEC4.memSize();
			}
		}
			break;

		default:
			assert(false);
		}

		return retVal;
	}
}