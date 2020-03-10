#include "ModelMatrixBuffer.h"
#include "ShaderIdentifier.h"
#include "VertexAttributeListFactory.h"
#include "Constant.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ModelMatrixBuffer::ModelMatrixBuffer(const size_t numInstances)
	{
		setAttributes(
			VertexAttributeListFactory::getInstance(Danburite::VertexAttributeType::MODELMAT16));

		setNumInstances(numInstances);
	}

	Transform &ModelMatrixBuffer::getTransform(const size_t idx) noexcept
	{
		return __transforms[idx];
	}

	void ModelMatrixBuffer::setNumInstances(const size_t numInstances) noexcept
	{
		__numInstances = numInstances;
		__transforms.resize(numInstances);
		__modelMatrices.resize(numInstances);

		memoryAlloc(__modelMatrices.data(), numInstances * sizeof(mat4), BufferUpdatePatternType::STREAM);
	}

	void ModelMatrixBuffer::update() noexcept
	{
		for (size_t i = 0; i < __numInstances; i++)
		{
			Transform &transform = __transforms[i];
			transform.update();

			__modelMatrices[i] = transform.getModelMatrix();
		}
	}

	void ModelMatrixBuffer::update(const vector<mat4> &parentModelMatrices) noexcept
	{
		for (size_t i = 0; i < __numInstances; i++)
		{
			Transform &transform = __transforms[i];
			transform.update();

			__modelMatrices[i] = (parentModelMatrices[i] * transform.getModelMatrix());
		}
	}

	void ModelMatrixBuffer::selfDeploy() noexcept
	{
		memoryCopy(__modelMatrices.data(), __numInstances * sizeof(mat4));
	}
}