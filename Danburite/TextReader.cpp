#include "TextReader.h"
#include <fstream>
#include <sstream>

using namespace std;

namespace ObjectGL
{
	string TextReader::read(const string_view &path)
	{
		ifstream fin(path.data());

		ostringstream oss;
		oss << fin.rdbuf();

		return oss.str();
	}
}