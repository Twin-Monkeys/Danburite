#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
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
		static const unordered_map<GLuint, string> bindingPointToNameMap =
		{
			{
				ShaderIdentifier::Value::UniformBlockBindingPoint::MATERIAL,
				ShaderIdentifier::Name::UniformBuffer::MATERIAL
			},
			{
				ShaderIdentifier::Value::UniformBlockBindingPoint::LIGHT,
				ShaderIdentifier::Name::UniformBuffer::LIGHT
			},
			{
				ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA,
				ShaderIdentifier::Name::UniformBuffer::CAMERA
			},
			{
				ShaderIdentifier::Value::UniformBlockBindingPoint::CONVOLUTION,
				ShaderIdentifier::Name::UniformBuffer::CONVOLUTION
			},
			{
				ShaderIdentifier::Value::UniformBlockBindingPoint::GAMMA_CORRECTION,
				ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION
			},
			{
				ShaderIdentifier::Value::UniformBlockBindingPoint::CUBEMAP,
				ShaderIdentifier::Name::UniformBuffer::CUBEMAP
			}
		};

		return make_shared<UniformBuffer>(bindingPointToNameMap.at(key), key);
	}
}