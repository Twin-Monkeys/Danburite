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
					SHININESS,

					AMBIENT_TEX,
					DIFFUSE_TEX,
					GAMMA,

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
					DEPTH_ATTACHMENT,
					STENCIL_ATTACHMENT,
					COLOR_ATTACHMENT_ARRAY[];
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

			namespace UniformBuffer
			{
				extern const std::string
					MATERIAL,
					LIGHT,
					CAMERA,
					CONVOLUTION,
					GAMMA_CORRECTION,
					SKYBOX,
					ATTACHMENT,
					DEPTH_BAKING_2D,
					DEPTH_BAKING_CUBEMAP
					;
			}
		}

		namespace Value
		{
			namespace VertexAttribute
			{
				constexpr GLuint
					POSITION_LOCATION = 0,
					COLOR_LOCATION = 1,
					NORMAL_LOCATION = 2,
					TEX_COORD_LOCATION = 3,
					TANGENT_LOCATION = 4,
					MODEL_MATRIX_LOCATION = 5
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
					ATTACHMENT				= 6U,
					DEPTH_BAKING_2D			= 7U,
					DEPTH_BAKING_CUBEMAP	= 8U
					;
			}

			namespace Light
			{
				constexpr GLuint
					MAX_NUM_LIGHTS = 7U;
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