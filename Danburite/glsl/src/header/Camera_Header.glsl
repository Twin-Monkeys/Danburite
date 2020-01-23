//? #version 460 core

#ifndef __CAMERA_HEADER__
#define __CAMERA_HEADER__

#include "Constant_Header.glsl"

struct Camera
{
	vec3 pos;
	mat4 viewMat;
	mat4 projMat;
};

layout(binding = BINDING_POINT_CAMERA) uniform UBCamera
{
	Camera camera;
};

vec3 Camera_getPosition()
{
	return camera.pos;
}

#endif