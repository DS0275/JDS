#include "pch.h"
#include "OglTri.h"

void OglTri::Draw(const OglTransform& tr)
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

    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, SIZE, 0.0f);     // top
    glVertex3f(-SIZE, -SIZE, 0.0f);    // left
    glVertex3f(SIZE, -SIZE, 0.0f);    // right
    glEnd();

    glEnd();

    glPopMatrix();
}
