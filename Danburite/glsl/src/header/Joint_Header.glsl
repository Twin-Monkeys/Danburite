//? #version 460 core

#ifndef __JOINT_HEADER__
#define __JOINT_HEADER__

#include "Constant_Header.glsl"

struct Joint
{
	mat4 jointMat;
};

layout(binding = BINDING_POINT_JOINT) uniform UBJoint
{
	Joint joint;
};

mat4 Joint_getJointMatrix()
{
	return joint.jointMat;
}

#endif