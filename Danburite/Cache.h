#pragma once

#include <unordered_map>

namespace ObjectGL
{
	template <typename KeyType, typename ValueType>
	class Cache abstract
	{
	private:
		std::unordered_map<KeyType, ValueType> __cacheMap;

	protected:
		virtual ValueType _onProvideValue(const KeyType &key) = 0;

	public:
		const ValueType &getValue(const KeyType &key);
		void clear() noexcept;
		bool clear(const KeyType &key) noexcept;

		virtual ~Cache() = default;
	};

	template <typename KeyType, typename ValueType>
	const ValueType &Cache<KeyType, ValueType>::getValue(const KeyType &key)
	{
		const auto it = __cacheMap.find(key);

		if (it != __cacheMap.end())
			return it->second;

		const auto &[_, retVal] = *__cacheMap.emplace(key, std::move(_onProvideValue(key))).first;
		return retVal;
	}

	template <typename KeyType, typename ValueType>
	void Cache<KeyType, ValueType>::clear() noexcept
	{
		__cacheMap.clear();
	}

	template <typename KeyType, typename ValueType>
	bool Cache<KeyType, ValueType>::clear(const KeyType &key) noexcept
	{
		return __cacheMap.erase(key);
	}
}