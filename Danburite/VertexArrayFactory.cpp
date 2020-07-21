#include "VertexArrayFactory.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "VertexAttributeListFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<VertexArray> VertexArrayFactory::createRectangle(const VertexAttributeFlag vertexFlag)
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
			if (vertexFlag & VertexAttributeFlag::POS)
			{
				const vec3 &pos = positions[i];
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });
			}

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			{
				const vec2 &texCoord = texCoords[i];
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
		}

		constexpr GLuint indices[] =
		{
			0, 1, 3, 1, 2, 3
		};

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));
	}

	shared_ptr<VertexArray> VertexArrayFactory::createCube(const VertexAttributeFlag vertexFlag)
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
			if (vertexFlag & VertexAttributeFlag::POS)
			{
				const vec3 &pos = positions[i];
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });
			}

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
			{
				const vec3 &normal = normals[i / 4];
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });
			}

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			{
				const vec2 &texCoord = texCoords[i % 4];
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (vertexFlag & VertexAttributeFlag::TANGENT)
			{
				const vec3 &tangent = tangents[i / 4];
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
			}
		}

		constexpr GLuint indices[] =
		{
			0, 1, 3, 1, 2, 3,
			4, 5, 7, 5, 6, 7,
			8, 9, 11, 9, 10, 11,
			12, 13, 15, 13, 14, 15,
			16, 17, 19, 17, 18, 19,
			20, 21, 23, 21, 22, 23
		};

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));
	}

	shared_ptr<VertexArray> VertexArrayFactory::createSphere(
		const VertexAttributeFlag vertexFlag, const size_t numStacks, const size_t numSectors)
	{
		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };

		vector<GLfloat> vertices;

		const float stackAngleStep = (pi<float>() / float(numStacks));
		const float sectorAngleStep = (two_pi<float>() / float(numSectors));

		float curStackAngle = half_pi<float>();
		for (size_t stackIter = 0ULL; stackIter <= numStacks; stackIter++)
		{
			vec3 pos;
			pos.y = sinf(curStackAngle);
			const float yProjLength = cosf(curStackAngle);

			float curSectorAngle = 0.f;
			for (size_t sectorIter = 0ULL; sectorIter <= numSectors; sectorIter++)
			{
				pos.x = (yProjLength * cosf(curSectorAngle));
				pos.z = (yProjLength * sinf(curSectorAngle));

				if (vertexFlag & VertexAttributeFlag::POS)
					vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });

				if (vertexFlag & VertexAttributeFlag::COLOR)
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

				if (vertexFlag & VertexAttributeFlag::NORMAL)
					vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });

				if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				{
					vertices.insert(
						vertices.end(), { float(sectorIter) / float(numSectors), float(stackIter) / float(numStacks) });
				}

				curSectorAngle += sectorAngleStep;
			}

			curStackAngle -= stackAngleStep;
		}

		vector<GLuint> indices;

		for (size_t stackIter = 0ULL; stackIter < numStacks; stackIter++)
		{
			GLuint idx0 = GLuint(stackIter * (numSectors + 1ULL));
			GLuint idx1 = (idx0 + GLuint(numSectors + 1ULL));

			for (size_t sectorIter = 0ULL; sectorIter < numSectors; sectorIter++)
			{
				if (stackIter)
					indices.insert(indices.end(), { idx0, idx1, idx0 + 1 });

				if (stackIter != GLuint(numStacks - 1ULL))
					indices.insert(indices.end(), { idx0 + 1, idx1, idx1 + 1 });

				idx0++;
				idx1++;
			}
		}

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(indices.size()));
	}
}