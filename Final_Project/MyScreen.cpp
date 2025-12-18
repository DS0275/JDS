#include "pch.h"
#include "MyScreen.h"
#include "OglTransform.h"

MyScreen::MyScreen(void)
{
	SetBackColor(RGB(0, 0, 255));
}

/*
void MyScreen::SampleMultiGameObj(void)
{
	// CArray: MFC가 제공하는 가변 배열; 크기 조정 가능(크기 조정할 때는 속도가 느려짐)
	CArray<OglTransform, OglTransform&> ar; // <,> 의미: template; < data type, argument(access) type>
	OglTransform ot;
	// #0 element
	ot.m_nType = GameObjType::SPHERE;
	ot.m_nColor = RGB(255, 0, 0);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(100.f, 100.f, 0.f);
	ot.m_scale = Vector3(0.5f, 1.f, 1.f);
	ar.Add(ot);
	// #1 element
	ot.m_nType = GameObjType::SPHERE;
	ot.m_nColor = RGB(0, 255, 0);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(-100.f, 100.f, 0.f);
	ot.m_scale = Vector3(1.f, 1.f, 1.f);
	ar.Add(ot);
	// #2 element
	ot.m_nType = GameObjType::CUBE;
	ot.m_nColor = RGB(0, 0, 255);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(-100.f, -100.f, 0.f);
	ot.m_scale = Vector3(1.f, 1.f, 1.f);
	ot.m_rotate = Vector3(45.f, 45.f, 0.f);
	ar.Add(ot);

	// #2 element
	ot.m_nType = GameObjType::CUBE;
	ot.m_nColor = RGB(0, 0, 0);
	ot.m_alpha = -1.f;
	ot.m_translate = Vector3(100.f, -100.f, 0.f);
	ot.m_scale = Vector3(2.f, 2.f, 2.f);
	ot.m_rotate = Vector3(45.f, 45.f, 0.f);
	ar.Add(ot);

	// #3 element
	ot.m_nType = GameObjType::CYLINDER;
	ot.m_nColor = RGB(255, 0, 255);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(0.f, 0.f, 0.f);
	ot.m_scale = Vector3(1.f, 1.f, 1.f);
	ot.m_rotate = Vector3(45.f, 0.f, 0.f);
	ar.Add(ot);

	// 배열의 모든 원소를 렌더링
	for (int i = 0; i < ar.GetCount(); i++)
	{
		OglTransform elt = ar[i]; // 현재 렌더링할 원소
		switch (elt.m_nType)
		{
		case GameObjType::SPHERE:
			m_sphere.Draw(elt);
			break;
		case GameObjType::CUBE:
			m_cube.Draw(elt);
			break;
		case GameObjType::CYLINDER:
			m_cylinder.Draw(elt);
			break;
		}
	}
}
*/

void MyScreen::InitOpenGL(void)
{
	OglScreen::InitOpenGL();

	StartRC();

	m_lightMtl.SetLightParam();
	m_sphere.Create();
	m_cylinder.Create();
	SetViewport();
	StopRC();
}

void MyScreen::InitRender(void)
{
	OglScreen::InitRender();

}

void MyScreen::RenderScene(void)
{
	glClearColor(m_clearR, m_clearG, m_clearB, m_clearA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// 매 프레임 Light 적용
	m_lightMtl.SetLightParam();

	OglScreen::RenderScene();
	DrawGrid();

	if (m_bAnimOn && m_nSelectedObjIndex >= 0)
	{
		m_animAngle += 1.0f;
		if (m_animAngle > 360.f) m_animAngle -= 360.f;

		m_arGameObj[m_nSelectedObjIndex].m_rotate.y = m_animAngle;
	}

	for (int i = 0; i < m_arGameObj.size(); i++)
	{
		if (m_nSelectedObjIndex != -1 && i != m_nSelectedObjIndex)
			continue;

		OglTransform& ot = m_arGameObj[i];

		// DEFAULT 일 때만 물체 색을 Diffuse로 직접 지정
		if (m_curLightPreset == LightPreset::DEFAULT)
		{
			float r = GetRValue(ot.m_nColor) / 255.0f;
			float g = GetGValue(ot.m_nColor) / 255.0f;
			float b = GetBValue(ot.m_nColor) / 255.0f;
			float diffuseColor[] = { r, g, b, ot.m_alpha };

			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		}

		switch (ot.m_nType)
		{
		case GameObjType::SPHERE:   m_sphere.Draw(ot);   break;
		case GameObjType::CUBE:     m_cube.Draw(ot);     break;
		case GameObjType::CYLINDER: m_cylinder.Draw(ot); break;
		case GameObjType::QUAD:     m_quad.Draw(ot);     break;
		case GameObjType::TRI:      m_tri.Draw(ot);      break;
		case GameObjType::PLANE:    m_plane.Draw(ot);    break;
		case GameObjType::CAPSULE:  m_capsule.Draw(ot);  break;
		}
	}
	//SampleMultiGameObj();
	//m_sphere.SetRgba(RGB(0, 255, 0));
	//m_sphere.Draw(100.);
	StopRC();

	if (m_bAnimOn)
		Invalidate(FALSE);
}

void MyScreen::AddGameObject(OglTransform& ot)
{
	m_arGameObj.push_back(ot);
	Invalidate(FALSE);
}

void MyScreen::SetBackgroundColor(float r, float g, float b, float a)
{
	m_clearR = r;
	m_clearG = g;
	m_clearB = b;
	m_clearA = a;
}

void MyScreen::DrawGrid()
{
	if (!m_bShowGrid) return;
	// Grid 크기 정의
	const int GRID_SIZE = 100;
	const float STEP = 10.0f;
	const float HALF_SIZE = (float)GRID_SIZE * STEP / 2.0f;

	glDisable(GL_LIGHTING); // Grid는 광원의 영향을 받지 않도록 함

	// 1. Grid 바닥 평면 (반투명 Quad) 렌더링
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 회색/흰색
	glColor4f(0.7f, 0.7f, 0.7f, 0.2f);

	glBegin(GL_QUADS);
	// 바닥 평면의 네 꼭짓점
	glVertex3f(HALF_SIZE, 0.0f, HALF_SIZE);
	glVertex3f(-HALF_SIZE, 0.0f, HALF_SIZE);
	glVertex3f(-HALF_SIZE, 0.0f, -HALF_SIZE);
	glVertex3f(HALF_SIZE, 0.0f, -HALF_SIZE);
	glEnd();

	glDisable(GL_BLEND);

	// 2. Grid 격자 선 렌더링
	glColor3f(0.5f, 0.5f, 0.5f); // 격자 선의 색상
	glLineWidth(1.0f);

	glBegin(GL_LINES);
	// Z축 평행선
	for (int i = 0; i <= GRID_SIZE; i++)
	{
		float x = (float)i * STEP - HALF_SIZE;
		glVertex3f(x, 0.0f, -HALF_SIZE);
		glVertex3f(x, 0.0f, HALF_SIZE);
	}
	// X축 평행선
	for (int i = 0; i <= GRID_SIZE; i++)
	{
		float z = (float)i * STEP - HALF_SIZE;
		glVertex3f(-HALF_SIZE, 0.0f, z);
		glVertex3f(HALF_SIZE, 0.0f, z);
	}
	glEnd();


	// 3. 축(Axis) 표시
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	// X축 (빨간색)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(HALF_SIZE, 0.0f, 0.0f);

	// Y축 (녹색)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, HALF_SIZE, 0.0f);

	// Z축 (파란색)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, HALF_SIZE);
	glEnd();

	glEnable(GL_LIGHTING);

}



