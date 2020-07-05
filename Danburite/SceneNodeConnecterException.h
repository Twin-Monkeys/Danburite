#pragma once

#include <exception>

namespace Danburite
{
	class SceneNodeConnecterException : public std::exception
	{
	public:
		SceneNodeConnecterException() = default;
		explicit SceneNodeConnecterException(char const* const _Message) noexcept;

		virtual ~SceneNodeConnecterException() = default;
	};
}