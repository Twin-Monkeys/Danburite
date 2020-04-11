#include "ShaderIdentifier.h"
#include <unordered_map>

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
					PROJ_VIEW_MATRIX = "projViewMat",
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

			namespace Skybox
			{
				const string
					ALBEDO_TEX = "skybox.albedoTex";
			}

			namespace DepthBaking2D
			{
				const string
					PROJ_VIEW_MATRIX = "depthBaking2D.projViewMat";
			}

			namespace DepthBakingCubemap
			{

			}

			namespace UniformBuffer
			{
				const string
					MATERIAL				= "UBMaterial",
					LIGHT					= "UBLight",
					CAMERA					= "UBCamera",
					CONVOLUTION				= "UBConvolution",
					GAMMA_CORRECTION		= "UBGammaCorrection",
					SKYBOX					= "UBSkybox",
					ATTACHMENT				= "UBAttachment",
					DEPTH_BAKING_2D			= "UBDepthBaking2D",
					DEPTH_BAKING_CUBEMAP	= "UBDepthBakingCubemap"
					;
			}
		}

		namespace Util
		{
			namespace UniformBuffer
			{
				GLuint getBindingPointFromName(const string &name) noexcept
				{
					static const unordered_map<string, GLuint> nameToBindingPointMap =
					{
						{
							Name::UniformBuffer::MATERIAL,
							Value::UniformBlockBindingPoint::MATERIAL
						},
						{
							Name::UniformBuffer::LIGHT,
							Value::UniformBlockBindingPoint::LIGHT
						},
						{
							Name::UniformBuffer::CAMERA,
							Value::UniformBlockBindingPoint::CAMERA
						},
						{
							Name::UniformBuffer::CONVOLUTION,
							Value::UniformBlockBindingPoint::CONVOLUTION
						},
						{
							Name::UniformBuffer::GAMMA_CORRECTION,
							Value::UniformBlockBindingPoint::GAMMA_CORRECTION
						},
						{
							Name::UniformBuffer::SKYBOX,
							Value::UniformBlockBindingPoint::SKYBOX
						},
						{
							Name::UniformBuffer::ATTACHMENT,
							Value::UniformBlockBindingPoint::ATTACHMENT
						},
						{
							Name::UniformBuffer::DEPTH_BAKING_2D,
							Value::UniformBlockBindingPoint::DEPTH_BAKING_2D
						},
						{
							Name::UniformBuffer::DEPTH_BAKING_CUBEMAP,
							Value::UniformBlockBindingPoint::DEPTH_BAKING_CUBEMAP
						}
					};

					return nameToBindingPointMap.at(name);
				}
			}
		}
	}
}