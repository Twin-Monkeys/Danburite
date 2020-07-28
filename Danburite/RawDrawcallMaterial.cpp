#include "RawDrawcallMaterial.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	RawDrawcallMaterial::RawDrawcallMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::MONO_COLOR, vertexFlag)
	{
		useLighting(false);
	}

	void RawDrawcallMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray &vertexArray, const GLsizei numInstances)
	{
		/*
			�θ� �����Լ��� noexcept �Ӽ��� ������ overriding �Լ����� ���� �� �ִ�.
			�׷��� �� �ݴ�� �ȵ�.
		*/
		throw MaterialException("RawDrawcallMaterial cannot use render function.");
	}

	void RawDrawcallMaterial::_onRawDrawcall(UniformSetter &, VertexArray& vertexArray, const GLsizei numInstances)
	{
		vertexArray.draw(numInstances);
	}
}