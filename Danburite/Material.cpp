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

	void Material::__setOption(const MaterialOptionFlag flags, const bool enabled) noexcept
	{
		if (enabled)
			__optionFlag |= flags;
		else
			__optionFlag &= ~flags;
	}

	void Material::useLighting(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::LIGHTING, enabled);
	}

	void Material::useAmbientTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::AMBIENT_TEXTURE, enabled);
	}

	void Material::useSpecularTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SPECULAR_TEXTURE, enabled);
	}

	void Material::useShininessTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::SHININESS_TEXTURE, enabled);
	}

	void Material::useAlphaTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::ALPHA_TEXTURE, enabled);
	}

	void Material::useNormalTexture(const bool enabled) noexcept
	{
		__setOption(MaterialOptionFlag::NORMAL_TEXTURE, enabled);
	}

	void Material::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
	}

	void Material::render(VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		__materialUniformSetter.setMaterialType(__MATERIAL_TYPE);
		__materialUniformSetter.setVertexType(__VERTEX_TYPE);
		__materialUniformSetter.setOptionFlag(__optionFlag);
		__materialUniformSetter.setGamma(__gamma);

		_onDeploy(__materialUniformSetter);
		_onRender(__materialUniformSetter, vertexArray, numInstances);
	}
}