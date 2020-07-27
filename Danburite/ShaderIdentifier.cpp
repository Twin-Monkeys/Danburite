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
					ENABLED				= "enabled",

					TYPE				= "type",
					ALBEDO				= "albedo",
					AMBIENT_STRENGTH	= "ambientStrength",
					DIFFUSE_STRENGTH	= "diffuseStrength",
					SPECULAR_STRENGTH	= "specularStrength",

					DIRECTION			= "direction",

					POSITION			= "pos",
					ATTENUATION_CONST	= "attConst",
					ATTENUATION_LINEAR	= "attLinear",
					ATTENUATION_QUAD	= "attQuad",
					VALID_DISTANCE		= "validDistance",

					INNER_CUTOFF		 = "innerCutOff",
					OUTER_CUTOFF		 = "outerCutOff",
					
					SHADOW_ENABLED		= "shadowEnabled",
					DEPTH_BAKING_TYPE	= "depthBakingType",
					DEPTH_MAP			= "depthMap",

					PROJ_VIEW_MATRIX	= "projViewMat",

					Z_FAR				= "zFar"
					;
			}

			namespace Material
			{
				const string
					TYPE = "material.type",
					OPTION_FLAG = "material.optionFlag",
					VERTEX_FLAG = "material.vertexFlag",

					DIFFUSE_COLOR = "material.diffuseColor",
					GAMMA = "material.gamma",

					EMISSIVE_STRENGTH = "material.emissiveStrength",
					SHININESS = "material.shininess",

					AMBIENT_TEX = "material.ambientTex",
					DIFFUSE_TEX = "material.diffuseTex",
					SPECULAR_TEX = "material.specularTex",
					EMISSIVE_TEX = "material.emissiveTex",
					SHININESS_TEX = "material.shininessTex",
					ALPHA_TEX = "material.alphaTex",
					NORMAL_TEX = "material.normalTex",
					HEIGHT_TEX = "material.heightTex",
					
					Z_NEAR = "material.zNear",
					Z_FAR = "material.zFar",
					
					OUTLINE_COLOR = "material.outlineColor",
					THICKNESS_RATIO = "material.thicknessRatio",
					
					ENVIRONMENT_TEX = "material.environmentTex";
			}

			namespace Attachment
			{
				const string
					TEX0 = "textureContainer.tex0",
					TEX1 = "textureContainer.tex1",
					TEX2 = "textureContainer.tex2",
					TEX3 = "textureContainer.tex3",
					TEX4 = "textureContainer.tex4",
					TEX5 = "textureContainer.tex5",
					TEX6 = "textureContainer.tex6",
					TEX7 = "textureContainer.tex7",
					TEX8 = "textureContainer.tex8",
					TEX9 = "textureContainer.tex9"
					;
			}

			namespace Convolutional
			{
				const string
					KERNEL_SIZE = "convolution.kernelSize",
					KERNEL = "convolution.kernel";
			}

			namespace GammaCorrection
			{
				const string
					GAMMA = "gammaCorrection.gamma";
			}

			namespace HDR
			{
				const string
					EXPOSURE = "hdr.exposure";
			}

			namespace Bloom
			{
				const string
					BRIGHTNESS_THRESHOLD = "bloom.brightnessThreshold",
					EFFECT_STRENGTH = "bloom.effectStrength";
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
				const std::string
					CENTER = "depthBakingCubemap.center",
					Z_FAR = "depthBakingCubemap.zFar",
					PROJ_VIEW_MATRICES = "depthBakingCubemap.projViewMatrices"
					;
			}

			namespace Joint
			{
				const string
					JOINT_MATRIX = "joint.jointMat";
			}

			namespace Animation
			{
				const string
					BONE_MATRICES = "animation.boneMatrices";
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
					TEX_CONTAINER			= "UBTextureContainer",
					DEPTH_BAKING_2D			= "UBDepthBaking2D",
					DEPTH_BAKING_CUBEMAP	= "UBDepthBakingCubemap",
					HDR						= "UBHDR",
					BLOOM					= "UBBloom",
					JOINT					= "UBJoint",
					BONE					= "UBBone"
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
							Name::UniformBuffer::TEX_CONTAINER,
							Value::UniformBlockBindingPoint::TEX_CONTAINER
						},
						{
							Name::UniformBuffer::DEPTH_BAKING_2D,
							Value::UniformBlockBindingPoint::DEPTH_BAKING_2D
						},
						{
							Name::UniformBuffer::DEPTH_BAKING_CUBEMAP,
							Value::UniformBlockBindingPoint::DEPTH_BAKING_CUBEMAP
						},
						{
							Name::UniformBuffer::HDR,
							Value::UniformBlockBindingPoint::HDR
						},
						{
							Name::UniformBuffer::BLOOM,
							Value::UniformBlockBindingPoint::BLOOM
						},
						{
							Name::UniformBuffer::JOINT,
							Value::UniformBlockBindingPoint::JOINT
						},
						{
							Name::UniformBuffer::BONE,
							Value::UniformBlockBindingPoint::BONE
						}
					};

					return nameToBindingPointMap.at(name);
				}
			}
		}
	}
}