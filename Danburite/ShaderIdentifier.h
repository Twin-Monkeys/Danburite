#pragma once

#include <string>
#include <gl/glew.h>

namespace Danburite
{
	namespace ShaderIdentifier
	{
		namespace Name
		{
			namespace Model
			{
				extern const std::string
					MODEL_MATRIX;
			}

			namespace Camera
			{
				extern const std::string
					POSITION,
					VIEW_MATRIX,
					PROJECTION_MATRIX;
			}

			namespace Light
			{
				extern const std::string
					NUM_LIGHTS;

				extern const std::string
					ENABLED,

					// base properties
					TYPE,
					ALBEDO,
					AMBIENT_STRENGTH,
					DIFFUSE_STRENGTH,
					SPECULAR_STRENGTH,

					// directional, spot
					DIRECTION,

					// point, spot
					POSITION,
					ATTENUATION_CONST,
					ATTENUATION_LINEAR,
					ATTENUATION_QUAD,
					VALID_DISTANCE,

					// spot
					INNER_CUTOFF,
					OUTER_CUTOFF,
					
					// shadow
					SHADOW_ENABLED,
					DEPTH_BAKING_TYPE,
					DEPTH_MAP,

					// ortho depth baking
					PROJ_VIEW_MATRIX,

					// cubemap depth baking
					Z_FAR
					;
			}

			namespace Material
			{
				extern const std::string
					TYPE,
					OPTION_FLAG,
					VERTEX_FLAG,

					DIFFUSE_COLOR,
					GAMMA,

					EMISSIVE_STRENGTH,
					SHININESS,

					AMBIENT_TEX,
					DIFFUSE_TEX,
					SPECULAR_TEX,
					EMISSIVE_TEX,
					SHININESS_TEX,
					ALPHA_TEX,
					NORMAL_TEX,
					HEIGHT_TEX,

					Z_NEAR,
					Z_FAR,

					OUTLINE_COLOR,
					THICKNESS_RATIO,
					
					ENVIRONMENT_TEX;
			}

			namespace Attachment
			{
				extern const std::string
					TEX0,
					TEX1,
					TEX2,
					TEX3,
					TEX4,
					TEX5,
					TEX6,
					TEX7,
					TEX8,
					TEX9
					;
			}

			namespace Convolutional
			{
				extern const std::string
					KERNEL_SIZE,
					KERNEL;
			}

			namespace GammaCorrection
			{
				extern const std::string
					GAMMA;
			}

			namespace HDR
			{
				extern const std::string
					EXPOSURE;
			}

			namespace Bloom
			{
				extern const std::string
					BRIGHTNESS_THRESHOLD,
					EFFECT_STRENGTH;
			}

			namespace Skybox
			{
				extern const std::string
					ALBEDO_TEX;
			}

			namespace DepthBaking2D
			{
				extern const std::string
					PROJ_VIEW_MATRIX;
			}

			namespace DepthBakingCubemap
			{
				extern const std::string
					CENTER,
					Z_FAR,
					PROJ_VIEW_MATRICES
					;
			}

			namespace Joint
			{
				extern const std::string
					JOINT_MATRIX;
			}

			namespace RenderingPipeline
			{
				extern const std::string
					TYPE;
			}

			namespace LightPrePass
			{
				extern const std::string
					CURRENT_LIGHT_IDX,
					LIGHT_AMBIENT_TEX,
					LIGHT_DIFFUSE_TEX,
					LIGHT_SPECULAR_TEX
					;
			}

			namespace UniformBuffer
			{
				extern const std::string
					MATERIAL,
					LIGHT,
					CAMERA,
					CONVOLUTION,
					GAMMA_CORRECTION,
					SKYBOX,
					TEX_CONTAINER,
					DEPTH_BAKING_2D,
					DEPTH_BAKING_CUBEMAP,
					HDR,
					BLOOM,
					JOINT,
					BONE,
					RENDERING_PIPELINE,
					LIGHT_PREPASS
					;
			}
		}

		namespace Value
		{
			namespace VertexAttribute
			{
				constexpr GLuint
					POSITION_LOCATION		= 0U,
					COLOR_LOCATION			= 1U,
					NORMAL_LOCATION			= 2U,
					TEX_COORD_LOCATION		= 3U,
					TANGENT_LOCATION		= 4U,
					BONE_INDICES_LOCATION	= 5U,
					BONE_WEIGHTS_LOCATION	= 6U,
					MODEL_MATRIX_LOCATION	= 7U
					;
			}

			namespace UniformBlockBindingPoint
			{
				constexpr GLuint
					MATERIAL				= 0U,
					LIGHT					= 1U,
					CAMERA					= 2U,
					CONVOLUTION				= 3U,
					GAMMA_CORRECTION		= 4U,
					SKYBOX					= 5U,
					TEX_CONTAINER			= 6U,
					DEPTH_BAKING_2D			= 7U,
					DEPTH_BAKING_CUBEMAP	= 8U,
					HDR						= 9U,
					BLOOM					= 10U,
					JOINT					= 11U,
					BONE					= 12U,
					RENDERING_PIPELINE		= 13U,
					LIGHT_PREPASS			= 14U
					;
			}

			namespace Light
			{
				constexpr GLuint
					MAX_NUM_LIGHTS = 256U;
			}

			namespace PostProcess
			{
				constexpr GLuint
					MAX_NUM_COLOR_ATTACHMENTS = 8U;
			}

			namespace MSAA
			{
				constexpr GLuint
					NUM_SAMPLE_POINTS = 4U;
			}

			namespace Convolutional
			{
				constexpr GLuint
					MAX_KERNEL_SIZE = 7U;
			}
		}

		namespace Util
		{
			namespace UniformBuffer
			{
				GLuint getBindingPointFromName(const std::string &name) noexcept;
			}
		}
	}
}