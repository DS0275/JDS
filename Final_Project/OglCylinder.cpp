#include "pch.h"
#include "OglCylinder.h"
#include "OglScreen.h"

OglCylinder::OglCylinder(void)
{
	m_pQobj = nullptr; // null pointer; NULLµµ °¡´É
	m_nColor = RGB(255, 0, 0);
	m_alpha = 1.0f;
}

OglCylinder::~OglCylinder()
{
	if (m_pQobj) gluDeleteQuadric(m_pQobj);
}

void OglCylinder::Create(void)
{
	if (m_pQobj) gluDeleteQuadric(m_pQobj);
	m_pQobj = gluNewQuadric();
	gluQuadricDrawStyle(m_pQobj, GLU_FILL);
	gluQuadricNormals(m_pQobj, GLU_SMOOTH);
}

void OglCylinder::Draw(GLdouble radius, GLdouble ht, GLint slice, GLint stack) const
{
	if (m_pQobj)
	{
		GLfloat r, g, b;
		OglScreen::colorrefToRgb(r, g, b, m_nColor);
		glColor4f(r, g, b, m_alpha); // glColor3f() ½áµµ µÊ: alpha = 1ÀÎ °æ¿ì
		gluCylinder(m_pQobj, radius, radius, ht, slice, stack); // gluSphere¿¡¼­ ÇÔ¼ö¸¸ ±³Ã¼

		// ¾Æ·¡ ¶Ñ²±
		glPushMatrix();
		glRotatef(180.f, 1.f, 0.f, 0.f);
		gluDisk(m_pQobj, 0.0, radius, slice, 1);
		glPopMatrix();

		// À§ ¶Ñ²±
		glPushMatrix();
		glTranslatef(0.f, 0.f, (GLfloat)ht);
		gluDisk(m_pQobj, 0.0, radius, slice, 1);
		glPopMatrix();
	}
}

void OglCylinder::Draw(const OglTransform& ot)
{
	glPushMatrix();
	glLoadIdentity();
	ot.Transform();
	SetRgba(ot.m_nColor, ot.m_alpha);
	DrawDef();
	glPopMatrix();
}

void OglCylinder::DrawDef(void)
{
	Draw(m_defRad, m_defRad * 4.);
}
