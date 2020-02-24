#include "ProgramFactory.h"
#include "ProgramPath.h"
#include <filesystem>
#include "ResourceManager.h"
#include "VertexShaderCompiler.h"
#include "GeometryShaderCompiler.h"
#include "FragmentShaderCompiler.h"

using namespace std;
using namespace filesystem;
using namespace ObjectGL;

namespace Danburite
{
	Program *ProgramFactory::__createProgram(const ProgramType type)
	{
		ResourceManager &resManager = ResourceManager::getInstance();
		
		const string &BIN_PATH = ProgramPath::getPath(ProgramPathType::BINARY, type);
		const string &VS_PATH = ProgramPath::getPath(ProgramPathType::VERTEX_SHADER, type);
		const string &GS_PATH = ProgramPath::getPath(ProgramPathType::GEOMETRY_SHADER, type);
		const string &FS_PATH = ProgramPath::getPath(ProgramPathType::FRAGMENT_SHADER, type);

		if (exists(BIN_PATH))
		{
			const file_time_type
				binLastModified = last_write_time(BIN_PATH),
				vsLastModified = ShaderCompiler::getLastModifiedTime(VS_PATH),
				fsLastModified = ShaderCompiler::getLastModifiedTime(FS_PATH);

			if ((binLastModified > vsLastModified) && (binLastModified > fsLastModified))
			{
				try
				{
					if (GS_PATH.empty())
						return new Program(*resManager.getRaw(BIN_PATH.data()));
					else
					{
						const file_time_type gsLastModified = ShaderCompiler::getLastModifiedTime(GS_PATH);

						if (binLastModified > gsLastModified)
							return new Program(*resManager.getRaw(BIN_PATH.data()));
					}
				}
				catch (const ProgramException &) {}
			}
		}

		unordered_set<shared_ptr<Shader>> shaders;

		VertexShaderCompiler vsCompiler;
		vsCompiler.addSource(VS_PATH);
		shaders.emplace(vsCompiler.compile());

		if (!GS_PATH.empty())
		{
			GeometryShaderCompiler gsCompiler;
			gsCompiler.addSource(GS_PATH);
			shaders.emplace(gsCompiler.compile());
		}

		FragmentShaderCompiler fsCompiler;
		fsCompiler.addSource(FS_PATH);
		shaders.emplace(fsCompiler.compile());

		Program *const pRetVal = new Program(shaders);
		resManager.storeRaw(BIN_PATH, pRetVal->exportBinary());

		return pRetVal;
	}

	Program &ProgramFactory::getProgram(const ProgramType type)
	{
		return *__programCache.getValue(type);
	}

	shared_ptr<Program> ProgramFactory::ProgramCache::_onProvideValue(const ProgramType &key)
	{
		return shared_ptr<Program>(__createProgram(key));
	}
}