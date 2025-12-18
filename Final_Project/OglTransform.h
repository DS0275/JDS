#pragma once

#include "Vector3.h"

enum class GameObjType
{
	NULL_DEF = 0, SPHERE, CUBE, CYLINDER, QUAD, TRI, PLANE, CAPSULE
};

// 게임 오브젝트 type, color, transform
class OglTransform
{
public:
	OglTransform(void);

	void SetDef(void);

	void Translate(void) const;
	void Rotate(void) const;
	void Scale(void) const;
	void Transform(void) const;

	//protected:
	GameObjType m_nType;
	COLORREF m_nColor;
	GLfloat m_alpha;
	Vector3 m_translate;	// 병진 운동: 유닛(unit)
	Vector3 m_rotate;		// 회전 운동: 각도(deg)
	Vector3 m_scale;		// 배율: 비율

	//COLORREF m_nColor = RGB(255, 255, 255); // 기본 색상
	//float m_alpha = 1.0f;

	// [재질 설정용 멤버 변수
	float m_fAmbient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };	// 주변광
	float m_fDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };	// 확산광
	float m_fSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 반사광
	float m_fShininess = 50.0f;

	UINT m_nTexID = 0;
};

