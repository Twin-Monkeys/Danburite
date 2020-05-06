#include "VertexArrayFactory.h"
#include <glm/glm.hpp>
#include "VertexAttributeListFactory.h"
#include "RenderContext.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<VertexArray> VertexArrayFactory::getVertexArrayPtr(
		const ShapeType shapeType, const VertexAttributeFlag vertexFlag)
	{
		return __cacheCache.getValue(shapeType)->getValue(vertexFlag);
	}

	VertexArray &VertexArrayFactory::
		getVertexArrayReference(const ShapeType shapeType, const VertexAttributeFlag vertexFlag)
	{
		return *(__cacheCache.getValue(shapeType)->getValue(vertexFlag));
	}

	shared_ptr<VertexArray> VertexArrayFactory::RectangleCache::_onProvideValue(const VertexAttributeFlag &key)
	{
		constexpr vec3 positions[] =
		{
			{ -1.f, -1.f, 0.f },
			{ 1.f, -1.f, 0.f },
			{ 1.f, 1.f, 0.f },
			{ -1.f, 1.f, 0.f }
		};

		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };
		constexpr vec3 normal = { 0.f, 0.f, 1.f };

		constexpr vec2 texCoords[] =
		{
			{ 0.f, 0.f },
			{ 1.f, 0.f },
			{ 1.f, 1.f },
			{ 0.f, 1.f }
		};

		constexpr vec3 tangent = { 1.f, 0.f, 0.f };

		vector<GLfloat> vertices;
		for (unsigned i = 0; i < 4; i++)
		{
			if (key & VertexAttributeFlag::POS3)
			{
				const vec3 &pos = positions[i];
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });
			}

			if (key & VertexAttributeFlag::COLOR4)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (key & VertexAttributeFlag::NORMAL3)
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });

			if (key & VertexAttributeFlag::TEXCOORD2)
			{
				const vec2 &texCoord = texCoords[i];
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (key & VertexAttributeFlag::TANGENT3)
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
		}

		const vector<VertexAttribute> &attribList = VertexAttributeListFactory::getInstance(key);

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(attribList);

		constexpr GLuint indices[] =
		{
			0, 1, 3, 1, 2, 3
		};

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));
	}

	shared_ptr<VertexArray> VertexArrayFactory::CubeCache::_onProvideValue(const VertexAttributeFlag &key)
	{
		constexpr vec3 positions[] =
		{
			// Top
			{ -1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, -1.f }, { -1.f, 1.f, -1.f },

			// Bottom
			{ -1.f, -1.f, -1.f }, { 1.f, -1.f, -1.f }, { 1.f, -1.f, 1.f }, { -1.f, -1.f, 1.f },

			// Right
			{ 1.f, -1.f, 1.f }, { 1.f, -1.f, -1.f }, { 1.f, 1.f, -1.f }, { 1.f, 1.f, 1.f },

			// Left
			{ -1.f, -1.f, -1.f }, { -1.f, -1.f, 1.f }, { -1.f, 1.f, 1.f }, { -1.f, 1.f, -1.f },

			// Forward
			{ -1.f, -1.f, 1.f }, { 1.f, -1.f, 1.f }, { 1.f, 1.f, 1.f }, { -1.f, 1.f, 1.f },

			// Backward
			{ 1.f, -1.f, -1.f }, { -1.f, -1.f, -1.f }, { -1.f, 1.f, -1.f }, { 1.f, 1.f, -1.f }
		};

		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };

		constexpr vec3 normals[] =
		{
			// Top
			{ 0.f, 1.f, 0.f },

			// Bottom
			{ 0.f, -1.f, 0.f },

			// Right
			{ 1.f, 0.f, 0.f },

			// Left
			{ -1.f, 0.f, 0.f },

			// Forward
			{ 0.f, 0.f, 1.f },

			// Backward
			{ 0.f, 0.f, -1.f }
		};

		constexpr vec2 texCoords[] =
		{
			{ 0.f, 0.f },
			{ 1.f, 0.f },
			{ 1.f, 1.f },
			{ 0.f, 1.f }
		};

		constexpr vec3 tangents[] =
		{
			// Top
			{ 1.f, 0.f, 0.f },

			// Bottom
			{ 1.f, 0.f, 0.f },

			// Right
			{ 0.f, 0.f, -1.f },

			// Left
			{ 0.f, 0.f, 1.f },

			// Forward
			{ 1.f, 0.f, 0.f },

			// Backward
			{ -1.f, 0.f, 0.f }
		};

		vector<GLfloat> vertices;
		for (unsigned i = 0; i < 24; i++)
		{
			if (key & VertexAttributeFlag::POS3)
			{
				const vec3 &pos = positions[i];
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });
			}

			if (key & VertexAttributeFlag::COLOR4)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (key & VertexAttributeFlag::NORMAL3)
			{
				const vec3 &normal = normals[i / 4];
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });
			}

			if (key & VertexAttributeFlag::TEXCOORD2)
			{
				const vec2 &texCoord = texCoords[i % 4];
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (key & VertexAttributeFlag::TANGENT3)
			{
				const vec3 &tangent = tangents[i / 4];
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
			}
		}

		const vector<VertexAttribute> &attribList = VertexAttributeListFactory::getInstance(key);

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(attribList);

		constexpr GLuint indices[] =
		{
			0, 1, 3, 1, 2, 3,
			4, 5, 7, 5, 6, 7,
			8, 9, 11, 9, 10, 11,
			12, 13, 15, 13, 14, 15,
			16, 17, 19, 17, 18, 19,
			20, 21, 23, 21, 22, 23
		};

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));
	}

	shared_ptr<Cache<VertexAttributeFlag, shared_ptr<VertexArray>>>
		VertexArrayFactory::CacheCache::_onProvideValue(const ShapeType &key)
	{
		switch (key)
		{
		case ShapeType::RECTANGLE:
			return make_shared<RectangleCache>();

		case ShapeType::CUBE:
			return make_shared<CubeCache>();
		}

		assert(false);
		return nullptr;
	}
}