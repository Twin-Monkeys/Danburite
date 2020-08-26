#pragma once

#include "RenderContext.h"
#include <any>
#include "DeferredUniformBuffer.h"
#include "TranslucencySwitcherUniformInterface.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"

namespace Danburite
{
	class UniformBufferFactory : public ObjectGL::ContextDependentSingleton<UniformBufferFactory>
	{
		friend ObjectGL::ContextDependentSingleton<UniformBufferFactory>;

	private:
		std::unordered_map<std::type_info, std::any> __uniformBufferCache;

		UniformBufferFactory() = default;

	public:
		template <typename $UniformInterfaceType>
		DeferredUniformBuffer<$UniformInterfaceType> &getUniformBuffer();
	};

	template <typename $UniformInterfaceType>
	DeferredUniformBuffer<$UniformInterfaceType> &UniformBufferFactory::getUniformBuffer()
	{
		using namespace std;
		using namespace ObjectGL;

		const type_info RTTI = typeid($UniformInterfaceType);
		auto resultIt = __uniformBufferCache.find(RTTI);

		if (resultIt != __uniformBufferCache.end())
			return *any_cast<shared_ptr<DeferredUniformBuffer<$UniformInterfaceType>>>(resultIt->second);

		DeferredUniformBuffer<$UniformInterfaceType> &retVal =
			*any_cast<shared_ptr<DeferredUniformBuffer<$UniformInterfaceType>>>(
				__uniformBufferCache.emplace(RTTI, make_shared<DeferredUniformBuffer<$UniformInterfaceType>>()).first.second);

		const string &blockName = retVal.getBlockName();
		ProgramFactory &programFactory = ProgramFactory::getInstance();

		for (const ProgramType programType : ProgramFactory::getUsingProgramsFromUniformBufferName(blockName))
			retVal.registerProgram(programFactory.getProgram(programType));

		retVal.memoryAllocFit(BufferUpdatePatternType::STREAM);
		return pRetVal;
	}
}
