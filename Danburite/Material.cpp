#include "Material.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Material::Material(
		const unordered_set<ProgramType> &programTypes,
		const MaterialType materialType, const VertexAttributeType vertexType) noexcept :
		__materialUniformSetter(programTypes), __MATERIAL_TYPE(materialType), __VERTEX_TYPE(vertexType)
	{
		using namespace ShaderIdentifier;
		static unordered_set<UniformSetter *> initializedSet;

		ProgramFactory &programFactory = ProgramFactory::getInstance();
		for (const ProgramType programType : programTypes)
		{
			UniformSetter *const pUniformSetter = &(programFactory.getProgram(programType));

			if (!initializedSet.emplace(pUniformSetter).second)
				continue;

			pUniformSetter->setTextureLocation(Name::Material::AMBIENT_TEX, Value::Material::AMBIENT_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::DIFFUSE_TEX, Value::Material::DIFFUSE_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::SPECULAR_TEX, Value::Material::SPECULAR_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::EMISSIVE_TEX, Value::Material::EMISSIVE_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::SHININESS_TEX, Value::Material::SHININESS_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::ALPHA_TEX, Value::Material::ALPHA_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::NORMAL_TEX, Value::Material::NORMAL_TEX_LOCATION);
			pUniformSetter->setTextureLocation(Name::Material::ENVIRONMENT_TEX, Value::Material::ENVIRONMENT_TEX_LOCATION);
		}
	}

	void Material::__render_normal(
		Material &instance, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		instance.__materialUniformSetter.setMaterialType(instance.__MATERIAL_TYPE);
		instance.__materialUniformSetter.setVertexType(instance.__VERTEX_TYPE);
		instance.__materialUniformSetter.setOptionFlag(instance.__optionFlag);
		instance.__materialUniformSetter.setGamma(__gamma);

		instance._onDeploy(instance.__materialUniformSetter);
		instance._onRender(instance.__materialUniformSetter, vertexArray, numInstances);
	}

	void Material::__render_depthBaking(
		Material &instance, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		ProgramFactory::getInstance().
			getProgram(ProgramType::DEPTH_BAKING).bind();

		vertexArray.draw(numInstances);
	}

	void Material::render(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__pRenderFunc(*this, vertexArray, numInstances);
	}
}