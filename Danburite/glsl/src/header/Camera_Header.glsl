//? #version 460 core

#ifndef __CAMERA_HEADER__
#define __CAMERA_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_CAMERA) uniform UBCamera
{
	// 64byte
	layout(offset = 0) mat4 viewMat;
	layout(offset = 64) mat4 projMat;

	// 16byte (std140Àº vec3µµ 16byte)
	layout(offset = 128) vec3 pos;
}
camera;

vec3 Camera_getPosition()
{
	return camera.pos;
}

mat4 Camera_getViewMatrix()
{
	return camera.viewMat;
}

mat4 Camera_getProjMatrix()
{
	return camera.projMat;
}

float Camera_getNear()
{
	const float a = camera.projMat[2][2];
	const float b = camera.projMat[3][2];

	return (b / (a - 1.f));
}

float Camera_getFar()
{
	const float a = camera.projMat[2][2];
	const float b = camera.projMat[3][2];

	return (b / (a + 1.f));
}

float Camera_getViewSpaceDepth(const float fragDepth)
{
	const float ndcZ = ((fragDepth * 2.f) - 1.f);
	const float near = Camera_getNear();
	const float far = Camera_getFar();

	return ((2.f * near * far) / ((near + far) + ((near - far) * ndcZ)));
}

#endif