#pragma once

#include "Program.h"
#include "ProgramType.h"
#include "Cache.h"
#include "RenderContext.h"

namespace Danburite
{
	class ProgramFactory : public ObjectGL::ContextDependentSingleton<ProgramFactory>
	{
		friend ObjectGL::ContextDependentSingleton<ProgramFactory>;

	private:
		enum class ProgramPathType : size_t
		{
			BINARY = 0,
			VERTEX_SHADER,
			GEOMETRY_SHADER,
			FRAGMENT_SHADER
		};

		class ProgramCache : public ObjectGL::Cache<ProgramType, std::shared_ptr<ObjectGL::Program>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::Program> _onProvideValue(const ProgramType &key) override;
		};

		static const std::string &__getProgramPath(const ProgramPathType pathType, const ProgramType programType) noexcept;

		ProgramCache __programCache;

		ProgramFactory() = default;
		static ObjectGL::Program *__createProgram(const ProgramType type);

	public:
		ObjectGL::Program &getProgram(const ProgramType type);
	};
}
