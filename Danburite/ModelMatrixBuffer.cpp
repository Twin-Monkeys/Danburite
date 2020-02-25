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

	const vector<mat4> &ModelMatrixBuffer::getModelMatrices() const noexcept
	{
		return __modelMatrices;
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
			__transforms[i].calcModelMatrix(Constant::Matrix::IDENTITY_MATRIX, __modelMatrices[i]);
	}

	void ModelMatrixBuffer::update(const vector<mat4> &parentModelMatrices) noexcept
	{
		for (size_t i = 0; i < __numInstances; i++)
			__transforms[i].calcModelMatrix(parentModelMatrices[i], __modelMatrices[i]);
	}

	void ModelMatrixBuffer::selfDeploy() noexcept
	{
		memoryCopy(__modelMatrices.data(), 0, __numInstances * sizeof(mat4));
	}
}