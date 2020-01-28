//? #version 460 core

#ifndef __CONSTANT_HEADER__
#define __CONSTANT_HEADER__

// Vertex Attributes //

const uint
	POSITION_LOCATION		= 0U,
	COLOR_LOCATION			= 1U,
	NORMAL_LOCATION			= 2U,
	TEX_COORD_LOCATION		= 3U;

const uint
	MODEL_MATRIX_LOCATION	= 4U;


// Uniform Block Binding Point
const uint
	BINDING_POINT_LIGHT		= 0U,
	BINDING_POINT_CAMERA	= 1U;


// Material //

const uint
	MATERIAL_TYPE_MONO_COLOR			= 0,
	MATERIAL_TYPE_PHONG					= 1,
	MATERIAL_TYPE_SILHOUETTE			= 2,
	MATERIAL_TYPE_OUTLINING_PHONG		= 3,
	MATERIAL_TYPE_TRANSPARENT_PHONG		= 4,
	MATERIAL_TYPE_REFLECTION			= 5,
	MATERIAL_TYPE_REFLECTION_PHONG		= 6,
	MATERIAL_TYPE_REFRACTION			= 7,
	MATERIAL_TYPE_EXPLODING_PHONG		= 8;

const uint
	MATERIAL_OPTION_FLAG_LIGHTING				= (1 << 0),
	MATERIAL_OPTION_FLAG_SHININESS_TEXTURE		= (1 << 1),
	MATERIAL_OPTION_FLAG_ALPHA_TEXTURE			= (1 << 2),
	MATERIAL_OPTION_FLAG_NORMAL_TEXTURE			= (1 << 3);

const uint
	MATERIAL_VERTEX_FLAG_POS3					= (1 << 0),
	MATERIAL_VERTEX_FLAG_COLOR4					= (1 << 1),
	MATERIAL_VERTEX_FLAG_NORMAL3				= (1 << 2),
	MATERIAL_VERTEX_FLAG_TEXCOORD2				= (1 << 3);


// Light //

const uint MAX_NUM_LIGHTS = 7;

const uint
	LIGHT_TYPE_DIRECTIONAL	= 0,
	LIGHT_TYPE_POINT		= 1,
	LIGHT_TYPE_SPOT			= 2;


// Post Process //

const uint NUM_SAMPLE_POINTS = 4U;

#endif