//? #version 460 core

#ifndef __CONSTANT_HEADER__
#define __CONSTANT_HEADER__


// Common

const float EPSILON = 1e-6f;
const uint FALSE = 0U;
const uint TRUE = 1U;


// Vertex Attributes //

const uint
	POSITION_LOCATION		= 0U,
	COLOR_LOCATION			= 1U,
	NORMAL_LOCATION			= 2U,
	TEX_COORD_LOCATION		= 3U,
	TANGENT_LOCATION		= 4U,
	BONE_INDICES_LOCATION	= 5U,
	BONE_WEIGHTS_LOCATION	= 6U,
	MODEL_MATRIX_LOCATION	= 7U
	;


// Uniform Block Binding Point

const uint
	BINDING_POINT_MATERIAL					= 0U,
	BINDING_POINT_LIGHT						= 1U,
	BINDING_POINT_CAMERA					= 2U,
	BINDING_POINT_CONVOLUTION				= 3U,
	BINDING_POINT_GAMMA_CORRECTION			= 4U,
	BINDING_POINT_SKYBOX					= 5U,
	BINDING_POINT_TEX_CONTAINER				= 6U,
	BINDING_POINT_DEPTH_BAKING_2D			= 7U,
	BINDING_POINT_DEPTH_BAKING_CUBEMAP		= 8U,
	BINDING_POINT_HDR						= 9U,
	BINDING_POINT_BLOOM						= 10U,
	BINDING_POINT_JOINT						= 11U,
	BINDING_POINT_BONE						= 12U,
	BINDING_POINT_PHONG						= 13U,
	BINDING_POINT_LIGHT_PREPASS				= 14U,
	BINDING_POINT_TRANSLUCENCY_SWITCHER		= 15U
	;


// Material //

const uint
	MATERIAL_TYPE_MONO_COLOR			= 0U,
	MATERIAL_TYPE_PHONG					= 1U,
	MATERIAL_TYPE_REFLECTION			= 2U,
	MATERIAL_TYPE_REFRACTION			= 3U,
	MATERIAL_TYPE_RAW_DRAWCALL			= 4U;

const uint
	MATERIAL_OPTION_FLAG_LIGHTING			= (1 << 0),
	MATERIAL_OPTION_FLAG_TRANSLUCENCY		= (1 << 1),
	MATERIAL_OPTION_FLAG_AMBIENT_TEXTURE	= (1 << 2),
	MATERIAL_OPTION_FLAG_DIFFUSE_TEXTURE	= (1 << 3),
	MATERIAL_OPTION_FLAG_SPECULAR_TEXTURE	= (1 << 4),
	MATERIAL_OPTION_FLAG_EMISSIVE_TEXTURE	= (1 << 5),
	MATERIAL_OPTION_FLAG_SHININESS_TEXTURE	= (1 << 6),
	MATERIAL_OPTION_FLAG_ALPHA_TEXTURE		= (1 << 7),
	MATERIAL_OPTION_FLAG_NORMAL_TEXTURE		= (1 << 8),
	MATERIAL_OPTION_FLAG_HEIGHT_TEXTURE		= (1 << 9),
	MATERIAL_OPTION_FLAG_ALPHA_OVERRIDING	= (1 << 10)
	;

const uint
	MATERIAL_VERTEX_FLAG_POS				= (1 << 0),
	MATERIAL_VERTEX_FLAG_COLOR				= (1 << 1),
	MATERIAL_VERTEX_FLAG_NORMAL				= (1 << 2),
	MATERIAL_VERTEX_FLAG_TEXCOORD			= (1 << 3),
	MATERIAL_VERTEX_FLAG_TANGENT			= (1 << 4),
	MATERIAL_VERTEX_FLAG_BONE				= (1 << 5)
	;


// Light //

const uint MAX_NUM_LIGHTS = 150U;

const uint
	LIGHT_TYPE_DIRECTIONAL	= 0U,
	LIGHT_TYPE_POINT		= 1U,
	LIGHT_TYPE_SPOT			= 2U;

const uint
	LIGHT_DEPTH_BAKING_TYPE_ORTHO		= 0U,
	LIGHT_DEPTH_BAKING_TYPE_CUBEMAP		= 1U
	;


// Post Process //

const uint MAX_NUM_COLOR_ATTACHMENTS = 8U;


// Bloom //

const uint NUM_BLOOM_BLUR_KERNELS = 59U;


// Convolution //

const uint MAX_KERNEL_SIZE = 5U;


// Texture Container

const uint MAX_TEXTURE_CONTAINER_ELEMS = 10U;


// MSAA //

const uint NUM_SAMPLE_POINTS = 4U;


// Animation

const uint MAX_NUM_BONES = 512U;


// Phong

const uint
	PHONG_CALC_METHOD_TYPE_FORWARD			= 0U,
	PHONG_CALC_METHOD_TYPE_LIGHT_PREPASS	= 1U
	;


// Light PrePass

const uint
	LIGHT_VOLUME_TYPE_FULLSCREEN	= 0U,
	LIGHT_VOLUME_TYPE_GEOMETRY		= 1U;


// Translucency Switcher

const uint
	TRANSLUCENCY_SWITCHER_MODE_OPAQUE			= 0U,
	TRANSLUCENCY_SWITCHER_MODE_TRANSLUCENCY		= 1U
	;

#endif