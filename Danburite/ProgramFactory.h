#pragma once

#include "Program.h"
#include "ProgramType.h"
#include "Cache.h"

namespace Danburite
{
	class ProgramFactory
	{
	private:
		class ProgramCache : public ObjectGL::Cache<ProgramType, std::shared_ptr<ObjectGL::Program>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::Program> _onProvideValue(const ProgramType &key) override;
		};

		ProgramCache __programCache;

		ProgramFactory() = default;

		static ObjectGL::Program *__createProgram(const ProgramType type);

	public:
		ObjectGL::Program &getProgram(const ProgramType type);

		static ProgramFactory &getInstance() noexcept;
	};
}
