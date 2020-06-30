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
			VertexAttributeListFactory::getInstance(VertexAttributeFlag::MODELMAT));

		setNumInstances(numInstances);
	}

	Transform &ModelMatrixBuffer::getTransform(const size_t idx) noexcept
	{
		return __transforms[idx];
	}

	size_t ModelMatrixBuffer::getNumInstances() const noexcept
	{
		return __modelMatrices.size();
	}

	void ModelMatrixBuffer::setNumInstances(const size_t numInstances) noexcept
	{
		__transforms.resize(numInstances);
		__modelMatrices.resize(numInstances, mat4 { 1.f });

		memoryAlloc(__modelMatrices.data(), numInstances * sizeof(mat4), BufferUpdatePatternType::STREAM);
	}

	void ModelMatrixBuffer::updateMatrices() noexcept
	{
		for (size_t i = 0; i < __modelMatrices.size(); i++)
		{
			Transform &transform = __transforms[i];
			transform.updateMatrix();

			__modelMatrices[i] = transform.getMatrix();
		}
	}

	void ModelMatrixBuffer::selfDeploy() noexcept
	{
		memoryCopy(__modelMatrices.data(), __modelMatrices.size() * sizeof(mat4));
	}
}