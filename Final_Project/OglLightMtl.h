#pragma once
#include <gl/GL.h>
#include "LightPreset.h"
#include "MaterialPreset.h"

class OglLightMtl
{
public:
    OglLightMtl();

    void ApplyLightPreset(LightPreset preset);
    void ApplyMaterialPreset(MaterialPreset preset);

    void SetLightParam(bool bStartRC = false);

private:
    GLfloat m_lightAmbient[4];
    GLfloat m_lightDiffuse[4];
    GLfloat m_lightSpecular[4];
    GLfloat m_lightPos[4];

    GLfloat m_mtlSpecular[4];
    GLfloat m_mtlShininess;
};
