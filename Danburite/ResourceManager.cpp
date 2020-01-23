#include "ResourceManager.h"
#include "TextReader.h"
#include <fstream>
#include <iterator>

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<const string> ResourceManager::getText(const string &path)
	{
		return __stringCache.getValue(path);
	}

	void ResourceManager::storeText(const string_view &path, const string_view &text)
	{
		ofstream { path.data() } << text.data();
	}

	shared_ptr<const vector<uint8_t>> ResourceManager::getRaw(const string &path)
	{
		return __rawCache.getValue(path);
	}

	void ResourceManager::storeRaw(const string_view &path, const vector<uint8_t> &data)
	{
		ofstream fout { path.data(), ofstream::binary };
		fout.unsetf(ifstream::skipws);

		fout.write(reinterpret_cast<const char *>(data.data()), data.size());
	}

	void ResourceManager::clearCache() noexcept
	{
		__stringCache.clear();
	}

	ResourceManager& ResourceManager::getInstance() noexcept
	{
		static ResourceManager instance;
		return instance;
	}

	shared_ptr<const string> ResourceManager::StringCache::_onProvideValue(const string &key)
	{
		return make_shared<string>(move(TextReader::read(key)));
	}

	shared_ptr<const vector<uint8_t>> ResourceManager::RawCache::_onProvideValue(const string &key)
	{
		shared_ptr<vector<uint8_t>> pRetVal = make_shared<vector<uint8_t>>();

		ifstream fin(key, ifstream::binary);
		fin.unsetf(ifstream::skipws);

		pRetVal->insert(pRetVal->begin(), istream_iterator<uint8_t>(fin), {});

		return pRetVal;
	}
}