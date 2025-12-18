#include "pch.h"
#include "OglLightMtl.h"

OglLightMtl::OglLightMtl()
{
    // 기본 위치
    m_lightPos[0] = 100.f;
    m_lightPos[1] = 100.f;
    m_lightPos[2] = 100.f;
    m_lightPos[3] = 1.f;

    ApplyLightPreset(LightPreset::DEFAULT);
    ApplyMaterialPreset(MaterialPreset::PLASTIC);
}

void OglLightMtl::ApplyLightPreset(LightPreset preset)
{
    switch (preset)
    {
    case LightPreset::DEFAULT:
        m_lightAmbient[0] = m_lightAmbient[1] = m_lightAmbient[2] = 0.2f;
        m_lightDiffuse[0] = m_lightDiffuse[1] = m_lightDiffuse[2] = 0.6f;
        m_lightSpecular[0] = m_lightSpecular[1] = m_lightSpecular[2] = 0.8f;
        break;

    case LightPreset::BRIGHT:
        m_lightAmbient[0] = m_lightAmbient[1] = m_lightAmbient[2] = 1.0f;
        m_lightDiffuse[0] = m_lightDiffuse[1] = m_lightDiffuse[2] = 1.0f;
        m_lightSpecular[0] = m_lightSpecular[1] = m_lightSpecular[2] = 1.0f;
        break;

    case LightPreset::DARK:
        m_lightAmbient[0] = m_lightAmbient[1] = m_lightAmbient[2] = 0.0f;
        m_lightDiffuse[0] = m_lightDiffuse[1] = m_lightDiffuse[2] = 0.0f;
        m_lightSpecular[0] = m_lightSpecular[1] = m_lightSpecular[2] = 0.0f;
        break;

    }

    m_lightAmbient[3] =
        m_lightDiffuse[3] =
        m_lightSpecular[3] = 1.0f;
}

void OglLightMtl::ApplyMaterialPreset(MaterialPreset preset)
{
    m_mtlSpecular[0] = m_mtlSpecular[1] = m_mtlSpecular[2] = 1.0f;
    m_mtlSpecular[3] = 1.0f;

    switch (preset)
    {
    case MaterialPreset::PLASTIC:
        m_mtlShininess = 32.0f;
        break;

    case MaterialPreset::METAL:
        m_mtlShininess = 96.0f;
        break;

    case MaterialPreset::MATTE:
        m_mtlShininess = 8.0f;
        break;
    }
}

void OglLightMtl::SetLightParam(bool bStartRC)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpecular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, m_mtlSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, m_mtlShininess);
}
