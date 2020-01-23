#pragma once

#include <exception>
#include <memory>

namespace ObjectGL
{
	class AssertException : public std::exception
	{
	public:
		AssertException() = default;
		explicit AssertException(char const* const _Message) noexcept;

		virtual ~AssertException() = default;

		static void test(const bool expression);

		template <typename T>
		static void test(const std::shared_ptr<T> &ptr);

		static void fail();
		static void glErrorTest();
	};

	template <typename T>
	void AssertException::test(const std::shared_ptr<T> &ptr)
	{
		test(ptr.get() != nullptr);
	}
}