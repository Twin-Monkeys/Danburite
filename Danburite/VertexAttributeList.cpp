#include "VertexAttributeList.h"

using namespace std;

namespace ObjectGL
{
	VertexAttributeList::VertexAttributeList(const vector<VertexAttribute> &entries) noexcept :
		__entries(entries)
	{}

	void VertexAttributeList::add(
		const GLuint location, const GLint numElements, const ElementType elementType,
		const GLsizei stride, const GLsizei offset, const GLuint divisor, const bool normalized) noexcept
	{
		__entries.emplace_back(
			location, VertexAttributeDataStructure{ numElements, elementType, normalized }, stride, offset, divisor);
	}

	void VertexAttributeList::add(
		const GLuint location, const VertexAttributeDataStructure& desc,
		const GLsizei stride, const GLsizei offset, const GLuint divisor) noexcept
	{
		__entries.emplace_back(location, desc, stride, offset, divisor);
	}

	void VertexAttributeList::add(const VertexAttribute& attribute) noexcept
	{
		__entries.emplace_back(attribute);
	}

	void VertexAttributeList::add(const VertexAttributeList& attributeList) noexcept
	{
		const vector<VertexAttribute> &additionalEntries = attributeList.__entries;

		__entries.insert(__entries.end(), additionalEntries.begin(), additionalEntries.end());
	}

	void VertexAttributeList::clear() noexcept
	{
		__entries.clear();
	}

	const vector<VertexAttribute>& VertexAttributeList::getEntries() const noexcept
	{
		return __entries;
	}

	VertexAttribute& VertexAttributeList::operator[](const size_t index) noexcept
	{
		return __entries[index];
	}

	const VertexAttribute& VertexAttributeList::operator[](const size_t index) const noexcept
	{
		return __entries[index];
	}
}