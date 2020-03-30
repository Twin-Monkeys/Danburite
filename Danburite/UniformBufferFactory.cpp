#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	UniformBuffer &UniformBufferFactory::getUniformBuffer(const GLuint uniformBlockBindingPoint)
	{
		return *__uniformBufferCache.getValue(uniformBlockBindingPoint);
	}

	shared_ptr<UniformBuffer> UniformBufferFactory::UniformBufferCache::_onProvideValue(const GLuint &key)
	{
		const string &bufferName =
			ShaderIdentifier::Util::UniformBuffer::getUniformBufferNameFromBindingPoint(key);

		const shared_ptr<UniformBuffer> &pRetVal = make_shared<UniformBuffer>(bufferName, key);

		const unordered_set<ProgramType> &targetProgramTypes =
			ShaderIdentifier::Util::UniformBuffer::getTargetProgramTypesFromBindingPoint(key);

		ProgramFactory &programFactory = ProgramFactory::getInstance();

		for (const ProgramType targetType : targetProgramTypes)
			pRetVal->registerProgram(programFactory.getProgram(targetType));

		return pRetVal;
	}
}