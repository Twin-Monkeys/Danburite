#include "VertexArrayFactory.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include "VertexAttributeListFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<VertexArray> VertexArrayFactory::createRectangle(const VertexAttributeFlag vertexFlag, const float edgeLength)
	{
		if (vertexFlag & (VertexAttributeFlag::BONE | VertexAttributeFlag::MODELMAT))
			throw VertexArrayFactoryException("Invalid flags are detected.");

		const float EDGE_HALF = (edgeLength * .5f);

		const vec3 positions[] =
		{
			{ -EDGE_HALF, 0.f, EDGE_HALF },
			{ EDGE_HALF, 0.f, EDGE_HALF },
			{ EDGE_HALF, 0.f, -EDGE_HALF },
			{ -EDGE_HALF, 0.f, -EDGE_HALF }
		};

		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };
		constexpr vec3 normal = { 0.f, 1.f, 0.f };

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

		constexpr GLubyte indices[] =
		{
			0U, 1U, 3U, 2U
		};

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);
		pIndexBuffer->setIndexType(IndexType::UNSIGNED_BYTE);

		const shared_ptr<VertexArray> &pRetVal =
			make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));

		pRetVal->setPrimitiveType(PrimitiveType::TRIANGLE_STRIP);
		return pRetVal;
	}

	shared_ptr<VertexArray> VertexArrayFactory::createCircle(
		const VertexAttributeFlag vertexFlag, const float radius, const size_t numSectors)
	{
		if ((vertexFlag & (VertexAttributeFlag::BONE | VertexAttributeFlag::MODELMAT)) ||
			(numSectors < 3ULL))
			throw VertexArrayFactoryException("Invalid flags are detected.");

		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };
		constexpr vec3 normal = { 0.f, 1.f, 0.f };
		constexpr vec3 tangent = { 1.f, 0.f, 0.f };

		const float sectorAngleStep = (two_pi<float>() / float(numSectors));

		vector<GLfloat> vertices;
		vector<GLuint> indices;

		GLuint curIdx = 0;
		indices.reserve(numSectors + 2ULL);

		if (vertexFlag & VertexAttributeFlag::POS)
			vertices.insert(vertices.end(), { 0.f, 0.f, 0.f });

		if (vertexFlag & VertexAttributeFlag::COLOR)
			vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

		if (vertexFlag & VertexAttributeFlag::NORMAL)
			vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });

		if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			vertices.insert(vertices.end(), { .5f, .5f });

		if (vertexFlag & VertexAttributeFlag::TANGENT)
			vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });

		indices.emplace_back(curIdx++);

		float curSectorAngle = 0.f;
		for (size_t sectorIter = 0ULL; sectorIter < numSectors; sectorIter++)
		{
			const vec2 &orient = { cosf(curSectorAngle), sinf(curSectorAngle) };
			const vec3 &pos = { (radius * orient.x), 0.f, -(radius * orient.y) };

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			{
				const vec2 &texCoord = ((orient + 1.f) * .5f);
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });

			indices.emplace_back(curIdx++);
			curSectorAngle += sectorAngleStep;
		}
		indices.emplace_back(1);

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		const shared_ptr<VertexArray> &pRetVal =
			make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(indices.size()));

		pRetVal->setPrimitiveType(PrimitiveType::TRIANGLE_FAN);
		return pRetVal;
	}

	shared_ptr<VertexArray> VertexArrayFactory::createCube(const VertexAttributeFlag vertexFlag, const float edgeLength)
	{
		if (vertexFlag & (VertexAttributeFlag::BONE | VertexAttributeFlag::MODELMAT))
			throw VertexArrayFactoryException("Invalid flags are detected.");

		const float EDGE_HALF = (edgeLength * .5f);

		const vec3 positions[] =
		{
			// Top
			{ -EDGE_HALF, edgeLength, EDGE_HALF },
			{ EDGE_HALF, edgeLength, EDGE_HALF },
			{ EDGE_HALF, edgeLength, -EDGE_HALF },
			{ -EDGE_HALF, edgeLength, -EDGE_HALF },

			// Bottom
			{ -EDGE_HALF, 0.f, -EDGE_HALF },
			{ EDGE_HALF, 0.f, -EDGE_HALF },
			{ EDGE_HALF, 0.f, EDGE_HALF },
			{ -EDGE_HALF, 0.f, EDGE_HALF },

			// Right
			{ EDGE_HALF, 0.f, EDGE_HALF },
			{ EDGE_HALF, 0.f, -EDGE_HALF },
			{ EDGE_HALF, edgeLength, -EDGE_HALF },
			{ EDGE_HALF, edgeLength, EDGE_HALF },

			// Left
			{ -EDGE_HALF, 0.f, -EDGE_HALF },
			{ -EDGE_HALF, 0.f, EDGE_HALF },
			{ -EDGE_HALF, edgeLength, EDGE_HALF },
			{ -EDGE_HALF, edgeLength, -EDGE_HALF },

			// Forward
			{ -EDGE_HALF, 0.f, EDGE_HALF },
			{ EDGE_HALF, 0.f, EDGE_HALF },
			{ EDGE_HALF, edgeLength, EDGE_HALF },
			{ -EDGE_HALF, edgeLength, EDGE_HALF },

			// Backward
			{ EDGE_HALF, 0.f, -EDGE_HALF },
			{ -EDGE_HALF, 0.f, -EDGE_HALF },
			{ -EDGE_HALF, edgeLength, -EDGE_HALF },
			{ EDGE_HALF, edgeLength, -EDGE_HALF }
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

		constexpr GLubyte indices[] =
		{
			0U, 1U, 3U, 1U, 2U, 3U,
			4U, 5U, 7U, 5U, 6U, 7U,
			8U, 9U, 11U, 9U, 10U, 11U,
			12U, 13U, 15U, 13U, 14U, 15U,
			16U, 17U, 19U, 17U, 18U, 19U,
			20U, 21U, 23U, 21U, 22U, 23U
		};

		const shared_ptr<VertexBuffer> &pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer> &pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);
		pIndexBuffer->setIndexType(IndexType::UNSIGNED_BYTE);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(size(indices)));
	}

	shared_ptr<VertexArray> VertexArrayFactory::createSphere(
		const VertexAttributeFlag vertexFlag, const float radius, const size_t numStacks, const size_t numSectors)
	{
		if ((vertexFlag & (VertexAttributeFlag::BONE | VertexAttributeFlag::MODELMAT)) ||
			(numStacks < 2ULL) || (numSectors < 3ULL))
			throw VertexArrayFactoryException("Invalid flags are detected.");

		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };

		const float stackAngleStep = (pi<float>() / float(numStacks));
		const float sectorAngleStep = (two_pi<float>() / float(numSectors));

		vector<GLfloat> vertices;

		float curStackAngle = half_pi<float>();
		for (size_t stackIter = 0ULL; stackIter <= numStacks; stackIter++)
		{
			vec3 localPos;
			localPos.y = (radius * sinf(curStackAngle));
			const float yProjLength = (radius * cosf(curStackAngle));

			float curSectorAngle = 0.f;
			for (size_t sectorIter = 0ULL; sectorIter <= numSectors; sectorIter++)
			{
				localPos.x = (yProjLength * cosf(curSectorAngle));
				localPos.z = -(yProjLength * sinf(curSectorAngle));

				if (vertexFlag & VertexAttributeFlag::POS)
				{
					const vec3 &finalPos = { localPos.x, localPos.y + radius, localPos.z };
					vertices.insert(vertices.end(), { finalPos.x, finalPos.y, finalPos.z });
				}

				if (vertexFlag & VertexAttributeFlag::COLOR)
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

				if (vertexFlag & VertexAttributeFlag::NORMAL)
				{
					const vec3 &normal = (localPos / radius);
					vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });
				}

				if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				{
					vertices.insert(
						vertices.end(), { float(sectorIter) / float(numSectors), float(stackIter) / float(numStacks) });
				}

				if (vertexFlag & VertexAttributeFlag::TANGENT)
				{
					vec3 tangent { localPos.z, 0.f, -localPos.x };
					const float tangentLength = length(tangent);

					if (epsilonEqual(tangentLength, 0.f, epsilon<float>()))
						tangent = { 1.f, 0.f, 0.f };
					else
						tangent /= tangentLength;

					vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });
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
					indices.insert(indices.end(), { idx0, idx1, idx0 + 1U });

				if (stackIter != GLuint(numStacks - 1ULL))
					indices.insert(indices.end(), { idx0 + 1U, idx1, idx1 + 1U });

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

	shared_ptr<VertexArray> VertexArrayFactory::createCylinder(
		const VertexAttributeFlag vertexFlag, const float topRadius, const float bottomRadius,
		const float height, const size_t numSectors)
	{
		if ((vertexFlag & (VertexAttributeFlag::BONE | VertexAttributeFlag::MODELMAT)) ||
			(numSectors < 3ULL) ||
			(epsilonEqual(topRadius, 0.f, epsilon<float>()) && epsilonEqual(bottomRadius, 0.f, epsilon<float>())) ||
			(height < epsilon<float>()))
			throw VertexArrayFactoryException("Invalid flags are detected.");

		constexpr vec4 color = { 1.f, 1.f, 1.f, 1.f };
		constexpr vec3 normal_top = { 0.f, 1.f, 0.f };
		constexpr vec3 normal_bottom = { 0.f, -1.f, 0.f };
		constexpr vec3 tangent_topBottom = { 1.f, 0.f, 0.f };

		const float sectorAngleStep = (two_pi<float>() / float(numSectors));

		vector<GLfloat> vertices;
		vector<GLuint> indices;
		GLuint baseIdx = 0U;


		// Top Lid //

		vector<vec3> topLidVertPositions;
		topLidVertPositions.reserve(numSectors);

		if (vertexFlag & VertexAttributeFlag::POS)
			vertices.insert(vertices.end(), { 0.f, height, 0.f });

		if (vertexFlag & VertexAttributeFlag::COLOR)
			vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

		if (vertexFlag & VertexAttributeFlag::NORMAL)
			vertices.insert(vertices.end(), { normal_top.x, normal_top.y, normal_top.z });

		if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			vertices.insert(vertices.end(), { .5f, .5f });

		if (vertexFlag & VertexAttributeFlag::TANGENT)
			vertices.insert(vertices.end(), { tangent_topBottom.x, tangent_topBottom.y, tangent_topBottom.z });

		float curSectorAngle = 0.f;
		for (size_t sectorIter = 0ULL; sectorIter < numSectors; sectorIter++)
		{
			const vec2& orient = { cosf(curSectorAngle), sinf(curSectorAngle) };
			const vec3& pos = { (topRadius * orient.x), height, -(topRadius * orient.y) };

			topLidVertPositions.emplace_back(pos);

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { normal_top.x, normal_top.y, normal_top.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			{
				const vec2& texCoord = ((orient + 1.f) * .5f);
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { tangent_topBottom.x, tangent_topBottom.y, tangent_topBottom.z });

			indices.emplace_back(baseIdx);
			indices.emplace_back(baseIdx + 1U + GLuint(sectorIter));
			indices.emplace_back(baseIdx + 1U + GLuint((sectorIter + 1) % numSectors));

			curSectorAngle += sectorAngleStep;
		}

		baseIdx += GLuint(numSectors + 1);


		// Bottom Lid //

		vector<vec3> bottomLidVertPositions;
		bottomLidVertPositions.reserve(numSectors);

		if (vertexFlag & VertexAttributeFlag::POS)
			vertices.insert(vertices.end(), { 0.f, 0.f, 0.f });

		if (vertexFlag & VertexAttributeFlag::COLOR)
			vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

		if (vertexFlag & VertexAttributeFlag::NORMAL)
			vertices.insert(vertices.end(), { normal_bottom.x, normal_bottom.y, normal_bottom.z });

		if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			vertices.insert(vertices.end(), { .5f, .5f });

		if (vertexFlag & VertexAttributeFlag::TANGENT)
			vertices.insert(vertices.end(), { tangent_topBottom.x, tangent_topBottom.y, tangent_topBottom.z });

		curSectorAngle = 0.f;
		for (size_t sectorIter = 0ULL; sectorIter < numSectors; sectorIter++)
		{
			const vec2& orient = { cosf(curSectorAngle), -sinf(curSectorAngle) };
			const vec3& pos = { (bottomRadius * orient.x), 0.f, (bottomRadius * orient.y) };

			bottomLidVertPositions.emplace_back(pos);

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { pos.x, pos.y, pos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { normal_bottom.x, normal_bottom.y, normal_bottom.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
			{
				const vec2& texCoord = ((orient + 1.f) * .5f);
				vertices.insert(vertices.end(), { texCoord.x, texCoord.y });
			}

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { tangent_topBottom.x, tangent_topBottom.y, tangent_topBottom.z });

			indices.emplace_back(baseIdx);
			indices.emplace_back(baseIdx + 1U + GLuint((sectorIter + 1) % numSectors));
			indices.emplace_back(baseIdx + 1U + GLuint(sectorIter));

			curSectorAngle += sectorAngleStep;
		}

		baseIdx += GLuint(numSectors + 1);


		// Side //

		for (size_t sectorIter = 0ULL; sectorIter < numSectors; sectorIter++)
		{
			const vec3 &curTopLidVertPos = topLidVertPositions[sectorIter];
			const vec3 &curBottomLidVertPos = bottomLidVertPositions[sectorIter];

			const vec3 &nextTopLidVertPos = topLidVertPositions[(sectorIter + 1) % numSectors];
			const vec3 &nextBottomLidVertPos = bottomLidVertPositions[(sectorIter + 1) % numSectors];

			vec3 curNormal;
			vec2 curProjNormal;
			vec3 curTangent;

			vec3 nextNormal;
			vec2 nextProjNormal;
			vec3 nextTangent;

			if (vertexFlag & VertexAttributeFlag::NORMAL)
			{
				if (topRadius > epsilon<float>())
				{
					curProjNormal = normalize(vec2 { curTopLidVertPos.x, curTopLidVertPos.z });
					nextProjNormal = normalize(vec2 { nextTopLidVertPos.x, nextTopLidVertPos.z });
				}
				else
				{
					curProjNormal = normalize(vec2 { curBottomLidVertPos.x, curBottomLidVertPos.z });
					nextProjNormal = normalize(vec2 { nextBottomLidVertPos.x, nextBottomLidVertPos.z });
				}

				const float slope = ((bottomRadius - topRadius) / height);
				curNormal = normalize(vec3 { curProjNormal.x, slope, curProjNormal.y });
				nextNormal = normalize(vec3 { nextProjNormal.x, slope, nextProjNormal.y });
			}
			
			if (vertexFlag & VertexAttributeFlag::TANGENT)
			{
				curTangent = normalize(vec3{ curProjNormal.y, 0.f, -curProjNormal.x });
				nextTangent = normalize(vec3{ nextProjNormal.y, 0.f, -nextProjNormal.x });
			}


			// cur top

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { curTopLidVertPos.x, curTopLidVertPos.y, curTopLidVertPos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { curNormal.x, curNormal.y, curNormal.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				vertices.insert(vertices.end(), { float(sectorIter) / float(numSectors), 1.f });

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { curTangent.x, curTangent.y, curTangent.z });


			// cur bottom

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { curBottomLidVertPos.x, curBottomLidVertPos.y, curBottomLidVertPos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { curNormal.x, curNormal.y, curNormal.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				vertices.insert(vertices.end(), { float(sectorIter) / float(numSectors), 0.f });

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { curTangent.x, curTangent.y, curTangent.z });


			// next top

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { nextTopLidVertPos.x, nextTopLidVertPos.y, nextTopLidVertPos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { nextNormal.x, nextNormal.y, nextNormal.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				vertices.insert(vertices.end(), { float(sectorIter + 1) / float(numSectors), 1.f });

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { nextTangent.x, nextTangent.y, nextTangent.z });


			// cur bottom

			if (vertexFlag & VertexAttributeFlag::POS)
				vertices.insert(vertices.end(), { nextBottomLidVertPos.x, nextBottomLidVertPos.y, nextBottomLidVertPos.z });

			if (vertexFlag & VertexAttributeFlag::COLOR)
				vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });

			if (vertexFlag & VertexAttributeFlag::NORMAL)
				vertices.insert(vertices.end(), { nextNormal.x, nextNormal.y, nextNormal.z });

			if (vertexFlag & VertexAttributeFlag::TEXCOORD)
				vertices.insert(vertices.end(), { float(sectorIter + 1) / float(numSectors), 0.f });

			if (vertexFlag & VertexAttributeFlag::TANGENT)
				vertices.insert(vertices.end(), { nextTangent.x, nextTangent.y, nextTangent.z });

			indices.emplace_back(baseIdx + GLuint(sectorIter * 4ULL));
			indices.emplace_back(baseIdx + GLuint(sectorIter * 4ULL) + 1U);
			indices.emplace_back(baseIdx + GLuint(sectorIter * 4ULL) + 3U);

			indices.emplace_back(baseIdx + GLuint(sectorIter * 4ULL));
			indices.emplace_back(baseIdx + GLuint(sectorIter * 4ULL) + 3U);
			indices.emplace_back(baseIdx + GLuint(sectorIter * 4ULL) + 2U);
		}

		const shared_ptr<VertexBuffer>& pVertexBuffer = make_shared<VertexBuffer>();
		pVertexBuffer->memoryAlloc(vertices, BufferUpdatePatternType::STATIC);
		pVertexBuffer->setAttributes(VertexAttributeListFactory::getInstance(vertexFlag));

		const shared_ptr<IndexBuffer>& pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->memoryAlloc(indices, BufferUpdatePatternType::STATIC);

		return make_shared<VertexArray>(pVertexBuffer, pIndexBuffer, GLsizei(indices.size()));
	}
}