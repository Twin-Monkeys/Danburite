#pragma once

#include <unordered_map>
#include <memory>

namespace Danburite
{
	template <typename T>
	class WeakPointerContainer
	{
	private:
		std::unordered_map<T *, std::weak_ptr<T>> __container;

	public:
		void add(const std::weak_ptr<T> &pContent) noexcept;
		void clear() noexcept;

		template <typename FunctionType, typename ...$Args>
		void safeTraverse(const FunctionType function, $Args &&...args);
	};

	template <typename T>
	void WeakPointerContainer<T>::add(const std::weak_ptr<T> &pContent) noexcept
	{
		__container.emplace(pContent.lock().get(), pContent);
	}

	template <typename T>
	void WeakPointerContainer<T>::clear() noexcept
	{
		__container.clear();
	}

	template <typename T>
	template <typename FunctionType, typename ...$Args>
	void WeakPointerContainer<T>::safeTraverse(const FunctionType function, $Args &&...args)
	{
		for (auto it = __container.begin(); it != __container.end();)
		{
			const std::shared_ptr<T> &pContent = it->second.lock();
			if (!pContent)
			{
				it = __container.erase(it);
				continue;
			}

			(pContent.get()->*function)(std::forward<$Args>(args)...);
			it++;
		}
	}
}