#include "pch.h"
#include "OglCapsule.h"

void OglCapsule::Draw(const OglTransform& tr)
{
    glPushMatrix();

    // 캡슐 전체 Transform
    tr.Transform();

    glColor4ub(
        GetRValue(tr.m_nColor),
        GetGValue(tr.m_nColor),
        GetBValue(tr.m_nColor),
        (GLubyte)(tr.m_alpha * 255)
    );

    const float R = 20.0f;   // 반지름
    const float H = 40.0f;   // 원통 높이

    GLUquadric* quad = gluNewQuadric();

    // 중앙 Cylinder
    glPushMatrix();
    glTranslatef(0.f, 0.f, -H * 0.5f);
    gluCylinder(quad, R, R, H, 24, 1);
    glPopMatrix();


    // 위 반구
    glPushMatrix();
    glTranslatef(0.f, 0.f, +H * 0.5f);
    gluSphere(quad, R, 24, 24);
    glPopMatrix();

    // 아래 반구
    glPushMatrix();
    glTranslatef(0.f, 0.f, -H * 0.5f);
    gluSphere(quad, R, 24, 24);
    glPopMatrix();

    gluDeleteQuadric(quad);
    glPopMatrix();
}