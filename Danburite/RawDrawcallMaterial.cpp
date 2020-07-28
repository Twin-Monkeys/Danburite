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
			부모 가상함수가 noexcept 속성이 없더라도 overriding 함수에는 붙일 수 있다.
			그러나 그 반대는 안됨.
		*/
		throw MaterialException("RawDrawcallMaterial cannot use render function.");
	}

	void RawDrawcallMaterial::_onRawDrawcall(UniformSetter &, VertexArray& vertexArray, const GLsizei numInstances)
	{
		vertexArray.draw(numInstances);
	}
}