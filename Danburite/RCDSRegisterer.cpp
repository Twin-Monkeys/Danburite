#include "RCDSRegisterer.h"
#include "RenderContext.h"
#include "VertexArrayFactory.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"

using namespace ObjectGL;

namespace Danburite
{
	void RCDSRegisterer::batchRegister() noexcept
	{
		RenderContext::registerContextDependentSingleton<VertexArrayFactory>();
		RenderContext::registerContextDependentSingleton<ProgramFactory>();
		RenderContext::registerContextDependentSingleton<UniformBufferFactory>();
	}
}