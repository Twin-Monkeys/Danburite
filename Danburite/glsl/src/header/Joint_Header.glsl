//? #version 460 core

#ifndef __JOINT_HEADER__
#define __JOINT_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_JOINT) uniform UBJoint
{
	layout(offset = 0) mat4 jointMat;
}
joint;

mat4 Joint_getJointMatrix()
{
	return joint.jointMat;
}

#endif