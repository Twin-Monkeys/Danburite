#include "Material.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	Material::Material(const MaterialType materialType, const VertexAttributeFlag vertexFlag) noexcept :
		__MATERIAL_TYPE(materialType), __VERTEX_FLAG(vertexFlag)
	{
		__defaultSetup.setup([this] (ContextStateManager &)
		{
			MaterialUniformInterface &materialInterface = __materialUB.getInterface();

			materialInterface.type = GLuint(__MATERIAL_TYPE);
			materialInterface.vertexFlag = GLuint(__VERTEX_FLAG);
			materialInterface.optionFlag = GLuint(__optionFlag);

			if (isAlphaOverridden())
				materialInterface.overriddenAlpha = __overriddenAlpha;
		});
	}

	void Material::render(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__defaultSetup();
		_onRender(__materialUB, vertexArray, numInstances);
	}

	void Material::rawDrawcall(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__defaultSetup();
		_onRawDrawcall(__materialUB, vertexArray, numInstances);
	}
}