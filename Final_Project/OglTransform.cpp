#include "pch.h"
#include "OglTransform.h"

OglTransform::OglTransform(void)
{
	SetDef();
}

void OglTransform::SetDef(void)
{
	m_nType = GameObjType::NULL_DEF;
	m_nColor = RGB(0, 0, 0);
	m_alpha = 1.0f;
	m_translate = Vector3(0.f, 0.f, 0.f);
	m_rotate = Vector3(0.f, 0.f, 0.f);
	m_scale = Vector3(1.f, 1.f, 1.f);

	m_fAmbient[0] = 0.2f; m_fAmbient[1] = 0.2f; m_fAmbient[2] = 0.2f; m_fAmbient[3] = 1.0f;
	m_fDiffuse[0] = 0.8f; m_fDiffuse[1] = 0.8f; m_fDiffuse[2] = 0.8f; m_fDiffuse[3] = 1.0f;
	m_fSpecular[0] = 1.0f; m_fSpecular[1] = 1.0f; m_fSpecular[2] = 1.0f; m_fSpecular[3] = 1.0f;
	m_fShininess = 50.0f;
}

void OglTransform::Translate(void) const
{
	glTranslatef(m_translate.x, m_translate.y, m_translate.z);
}

void OglTransform::Rotate(void) const
{
	glRotatef(m_rotate.x, 1.f, 0.f, 0.f); // x축 기준으로 회전
	glRotatef(m_rotate.y, 0.f, 1.f, 0.f); // y축 기준으로 회전
	glRotatef(m_rotate.z, 0.f, 0.f, 1.f); // z축 기준으로 회전
}

void OglTransform::Scale(void) const
{
	glScalef(m_scale.x, m_scale.y, m_scale.z);
}

void OglTransform::Transform(void) const
{
	Rotate();
	Translate();
	Scale();
}
