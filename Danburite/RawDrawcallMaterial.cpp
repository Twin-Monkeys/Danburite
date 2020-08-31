#include "RawDrawcallMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	RawDrawcallMaterial::RawDrawcallMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::MONO_COLOR, vertexFlag)
	{
		enableLighting(false);
	}

	void RawDrawcallMaterial::_onRender(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray &vertexArray, const GLsizei numInstances)
	{
		/*
			�θ� �����Լ��� noexcept �Ӽ��� ������ overriding �Լ����� ���� �� �ִ�.
			�׷��� �� �ݴ�� �ȵ�.
		*/
		throw MaterialException("RawDrawcallMaterial cannot use render function.");
	}

	void RawDrawcallMaterial::_onRawDrawcall(
		DeferredUniformBuffer<MaterialUniformInterface> &materialUB, VertexArray& vertexArray, const GLsizei numInstances)
	{
		vertexArray.draw(numInstances);
	}
}