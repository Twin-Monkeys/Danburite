#pragma once

#include <memory>
#include <unordered_map>
#include "Cache.h"

namespace Danburite
{
	class ResourceManager
	{
	private:
		class StringCache : public ObjectGL::Cache<std::string, std::shared_ptr<const std::string>>
		{
		protected:
			virtual std::shared_ptr<const std::string> _onProvideValue(const std::string &key) override;

		public:
			virtual ~StringCache() = default;
		};

		class RawCache : public ObjectGL::Cache<std::string, std::shared_ptr<const std::vector<std::uint8_t>>>
		{
		protected:
			virtual std::shared_ptr<const std::vector<std::uint8_t>> _onProvideValue(const std::string &key) override;

		public:
			virtual ~RawCache() = default;
		};

		StringCache __stringCache;
		RawCache __rawCache;

		ResourceManager() = default;

	public:
		std::shared_ptr<const std::string> getText(const std::string& path);
		void storeText(const std::string_view &path, const std::string_view &text);

		std::shared_ptr<const std::vector<std::uint8_t>> getRaw(const std::string &path);
		void storeRaw(const std::string_view &path, const std::vector<std::uint8_t> &data);

		void clearCache() noexcept;
		virtual ~ResourceManager() = default;

		static ResourceManager &getInstance() noexcept;
	};
}
