//? #version 460 core

#ifndef __VERTEX_ATTRIBUTE_HEADER__
#define __VERTEX_ATTRIBUTE_HEADER__

#include "Constant_Header.glsl"

layout(location = POSITION_LOCATION) in vec3 VertexAttribute_pos;
layout(location = COLOR_LOCATION) in vec4 VertexAttribute_color;
layout(location = NORMAL_LOCATION) in vec3 VertexAttribute_normal;
layout(location = TEX_COORD_LOCATION) in vec2 VertexAttribute_texCoord;
layout(location = TANGENT_LOCATION) in vec3 VertexAttribute_tangent;
layout(location = MODEL_MATRIX_LOCATION) in mat4 VertexAttribute_modelMat;

#endif