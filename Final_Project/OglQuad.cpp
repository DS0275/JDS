#include "pch.h"
#include "OglQuad.h"
#include "OglTransform.h" // OglTransform 사용을 위해 필요

void OglQuad::Draw(const OglTransform& tr)
{
    glPushMatrix();

    // Transform 적용
    tr.Transform();

    // 재질 설정 (광원 계산을 위해 OglTransform의 재질 정보를 사용)
    //glMaterialfv(GL_FRONT, GL_AMBIENT, tr.m_fAmbient);
    //float r = GetRValue(tr.m_nColor) / 255.0f;
    //float g = GetGValue(tr.m_nColor) / 255.0f;
    //float b = GetBValue(tr.m_nColor) / 255.0f;
    //float diffuseColor[] = { r, g, b, tr.m_alpha };
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, tr.m_fSpecular);
    //glMaterialf(GL_FRONT, GL_SHININESS, tr.m_fShininess);

    // 텍스처 활성화 및 바인딩
    if (tr.m_nTexID != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tr.m_nTexID);
        // 텍스처 사용 시 glColor는 흰색(1.0, 1.0, 1.0)으로 설정해야 텍스처 본연의 색이 나옴
        glColor4f(1.0f, 1.0f, 1.0f, tr.m_alpha);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
        // 텍스처를 사용하지 않을 경우, 기본 색상(Diffuse)을 덮어씁니다.
        glColor4ub(GetRValue(tr.m_nColor), GetGValue(tr.m_nColor), GetBValue(tr.m_nColor), (GLubyte)(tr.m_alpha * 255));
    }


    const float SIZE = 50.0f;

    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, 1.0f); // 노멀 벡터 (Z축 방향)

    // 정점 순서와 텍스처 좌표 매핑 (좌표 범위: 0.0 ~ 1.0)
    if (tr.m_nTexID != 0) glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-SIZE, -SIZE, 0.0f);

    if (tr.m_nTexID != 0) glTexCoord2f(1.0f, 0.0f);
    glVertex3f(SIZE, -SIZE, 0.0f);

    if (tr.m_nTexID != 0) glTexCoord2f(1.0f, 1.0f);
    glVertex3f(SIZE, SIZE, 0.0f);

    if (tr.m_nTexID != 0) glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-SIZE, SIZE, 0.0f);

    glEnd();

    // 텍스처 비활성화
    if (tr.m_nTexID != 0)
    {
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glPopMatrix();
}