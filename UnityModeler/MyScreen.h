#pragma once

#include "OglScreen.h"
#include "OglLightMtl.h"
#include "OglSphere.h"
#include "OglCube.h"
#include "OglCylinder.h"
#include "OglTransform.h"

class MyScreen :
	public OglScreen
{
public:
	MyScreen(void);

	// 사용자 GameObject 저장용 CArray
	CArray<OglTransform, OglTransform&> m_arGameObj;

	// 외부에서 GameObject 추가
	void AddGameObject(OglTransform& ot);

protected:
	OglLightMtl m_lightMtl;
	OglSphere m_sphere;
	OglCube m_cube;
	OglCylinder m_cylinder;

	//void SampleMultiGameObj(void);

	virtual void InitOpenGL(void);
	virtual void InitRender(void);
	virtual void RenderScene(void);
};

