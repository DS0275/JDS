#include "pch.h"
#include "OglPlane.h"

void OglPlane::Draw(const OglTransform& tr)
{
    glPushMatrix();

    tr.Transform();

    glColor4ub(
        GetRValue(tr.m_nColor),
        GetGValue(tr.m_nColor),
        GetBValue(tr.m_nColor),
        (GLubyte)(tr.m_alpha * 255)
    );

    const float SIZE = 50.0f;

    glBegin(GL_QUADS);
    glVertex3f(-SIZE, 0.0f, -SIZE);
    glVertex3f(-SIZE, 0.0f, SIZE);
    glVertex3f(SIZE, 0.0f, SIZE);
    glVertex3f(SIZE, 0.0f, -SIZE);
    glEnd();


    glPopMatrix();
}
