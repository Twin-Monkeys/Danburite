#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	UniformBuffer &UniformBufferFactory::getUniformBuffer(const string &bufferName)
	{
		return *__uniformBufferCache.getValue(bufferName);
	}

	shared_ptr<UniformBuffer> UniformBufferFactory::UniformBufferCache::_onProvideValue(const string &key)
	{
		ProgramFactory &programFactory = ProgramFactory::getInstance();

		const GLuint bindingPoint = ShaderIdentifier::Util::UniformBuffer::getBindingPointFromName(key);
		const shared_ptr<UniformBuffer> pRetVal = make_shared<UniformBuffer>(key, bindingPoint);

		for (const ProgramType programType : ProgramFactory::getUsingProgramsFromUniformBufferName(key))
			pRetVal->registerProgram(programFactory.getProgram(programType));

		return pRetVal;
	}
}