#include "ShaderIdentifier.h"

using namespace std;

namespace Danburite
{
	namespace ShaderIdentifier
	{
		namespace Name
		{
			namespace Model
			{
				const string
					MODEL_MATRIX = "model.modelMat";
			}
			 
			namespace Camera
			{
				const string
					POSITION = "camera.pos",
					VIEW_MATRIX = "camera.viewMat",
					PROJECTION_MATRIX = "camera.projMat";
			}

			namespace Light
			{
				const string
					ENABLED = "enabled",
					TYPE = "type",

					ALBEDO = "albedo",
					AMBIENT_STRENGTH = "ambientStrength",
					DIFFUSE_STRENGTH = "diffuseStrength",
					SPECULAR_STRENGTH = "specularStrength",

					POSITION = "pos",
					DIRECTION = "direction",
					ATTENUATION_CONST = "attConst",
					ATTENUATION_LINEAR = "attLinear",
					ATTENUATION_QUAD = "attQuad",

					INNER_CUTOFF = "innerCutOff",
					OUTER_CUTOFF = "outerCutOff",
					
					SHADOW_ENABLED = "shadowEnabled",
					VIEW_MATRIX = "viewMat",
					PROJECTION_MATRIX = "projMat",
					DEPTH_MAP = "depthMap";
			}

			namespace Material
			{
				const string
					TYPE = "material.type",
					OPTION_FLAG = "material.optionFlag",
					VERTEX_FLAG = "material.vertexFlag",

					DIFFUSE_COLOR = "material.diffuseColor",
					SHININESS = "material.shininess",

					AMBIENT_TEX = "material.ambientTex",
					DIFFUSE_TEX = "material.diffuseTex",
					GAMMA = "material.gamma",

					SPECULAR_TEX = "material.specularTex",
					EMISSIVE_TEX = "material.emissiveTex",
					SHININESS_TEX = "material.shininessTex",
					ALPHA_TEX = "material.alphaTex",
					NORMAL_TEX = "material.normalTex",
					
					Z_NEAR = "material.zNear",
					Z_FAR = "material.zFar",
					
					OUTLINE_COLOR = "material.outlineColor",
					THICKNESS_RATIO = "material.thicknessRatio",
					
					ENVIRONMENT_TEX = "material.environmentTex";
			}

			namespace Attachment
			{
				const string
					DEPTH_ATTACHMENT = "attachment.depth",
					STENCIL_ATTACHMENT = "attachment.stencil",
					
					COLOR_ATTACHMENT_ARRAY[] =
					{
						"attachment.colors[0]",
						"attachment.colors[1]",
						"attachment.colors[2]",
						"attachment.colors[3]",
						"attachment.colors[4]",
						"attachment.colors[5]",
						"attachment.colors[6]",
						"attachment.colors[7]"
					};
			}

			namespace Convolutional
			{
				const string
					KERNEL_SIZE = "convolution.kernelSize",
					KERNEL = "convolution.kernel";
			}

			namespace GammaCorrection
			{
				const std::string
					GAMMA = "gammaCorrection.gamma";
			}

			namespace Cubemap
			{
				const string
					ALBEDO_TEX = "cubemap.albedoTex";
			}

			namespace UniformBuffer
			{
				extern const string
					MATERIAL = "UBMaterial",
					LIGHT = "UBLight",
					CAMERA = "UBCamera",
					CONVOLUTION = "UBConvolution",
					GAMMA_CORRECTION = "UBGammaCorrection",
					CUBEMAP = "UBCubemap",
					ATTACHMENT = "UBAttachment";
			}
		}

		namespace Util
		{
			namespace UniformBuffer
			{
				const string &getUniformBufferNameFromBindingPoint(const GLuint bindingPoint) noexcept
				{
					static const string *const bindingPointToNameMap[] =
					{
						&Name::UniformBuffer::MATERIAL,
						&Name::UniformBuffer::LIGHT,
						&Name::UniformBuffer::CAMERA,
						&Name::UniformBuffer::CONVOLUTION,
						&Name::UniformBuffer::GAMMA_CORRECTION,
						&Name::UniformBuffer::CUBEMAP,
						&Name::UniformBuffer::ATTACHMENT
					};

					return *bindingPointToNameMap[bindingPoint];
				}

				const unordered_set<ProgramType> &getTargetProgramTypesFromBindingPoint(const GLuint bindingPoint) noexcept
				{
					static const unordered_set<ProgramType> bindingPointToTargetTypeSet[] =
					{
						// Material
						{
							ProgramType::MONO_COLOR,
							ProgramType::PHONG,
							ProgramType::SILHOUETTE,
							ProgramType::OUTLINE,
							ProgramType::SKYBOX
						},

						// Light
						{
							ProgramType::PHONG
						},

						// Camera
						{
							ProgramType::MONO_COLOR,
							ProgramType::PHONG,
							ProgramType::SILHOUETTE,
							ProgramType::OUTLINE,
							ProgramType::SKYBOX,
							ProgramType::DEPTH_BAKING
						},

						// Convolution
						{
							ProgramType::POST_PROCESS_CONVOLUTIONAL
						},

						// Gamma Correction
						{
							ProgramType::POST_PROCESS_GAMMA_CORRECTION
						},

						// Cubemap
						{
							ProgramType::SKYBOX
						},

						// Attachment
						{
							ProgramType::POST_PROCESS_FORWARD,
							ProgramType::POST_PROCESS_NEGATIVE,
							ProgramType::POST_PROCESS_GRAYSCALE,
							ProgramType::POST_PROCESS_CONVOLUTIONAL,
							ProgramType::POST_PROCESS_MSAA,
							ProgramType::POST_PROCESS_GAMMA_CORRECTION
						}
					};

					return bindingPointToTargetTypeSet[bindingPoint];
				}
			}
		}
	}
}