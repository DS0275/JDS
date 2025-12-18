#pragma once
#include "OglTransform.h"
#include "OglSphere.h"
#include "OglCylinder.h"

class OglCapsule
{
public:
    void Draw(const OglTransform& tr);

private:
    OglSphere   m_sphere;
    OglCylinder m_cylinder;
};
