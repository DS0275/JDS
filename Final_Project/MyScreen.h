#pragma once

#include "OglScreen.h"
#include "OglLightMtl.h"
#include "OglSphere.h"
#include "OglCube.h"
#include "OglCylinder.h"
#include "OglTransform.h"
#include "OglQuad.h"
#include "OglTri.h"
#include "OglPlane.h"
#include "OglCapsule.h"
#include "LightPreset.h"
#include <vector>


class MyScreen :
	public OglScreen
{
public:
	MyScreen(void);

	// 사용자 GameObject 저장용 CArray
	//CArray<OglTransform, OglTransform&> m_arGameObj;

	// 외부에서 GameObject 추가
	void AddGameObject(OglTransform& ot);

	float m_clearR, m_clearG, m_clearB, m_clearA;

	void SetBackgroundColor(float r, float g, float b, float a);

	// Grid on/off 상태
	bool m_bShowGrid = true;

	// 광원/재질 관리 객체
	OglLightMtl m_lightMtl;

	// 현재 선택된 오브젝트의 인덱스 (CDlgLight가 접근 가능해야 함)
	int m_nSelectedObjIndex = -1;

	// 게임 오브젝트 목록 (CDlgLight가 접근 가능해야 함)
	std::vector<OglTransform> m_arGameObj;

	LightPreset m_curLightPreset = LightPreset::DEFAULT;

	//애니메이션
	bool  m_bAnimOn = false;
	float m_animAngle = 0.f;



protected:
	OglSphere	m_sphere;
	OglCube		m_cube;
	OglCylinder m_cylinder;
	OglQuad     m_quad;
	OglTri      m_tri;
	OglPlane    m_plane;
	OglCapsule  m_capsule;

	//void SampleMultiGameObj(void);

	virtual void InitOpenGL(void);
	virtual void InitRender(void);

	void DrawGrid(void); // Grid를 그리는 함수
	virtual void RenderScene(void);
};

