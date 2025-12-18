#pragma once
#include "pch.h"
#include "afxdialogex.h"
#include "OglTransform.h" // OglTransform 사용을 위해 필요

class MyScreen; // MyScreen 클래스 전방 선언

// CDlgLight 대화 상자

class CDlgLight : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLight)

public:
	CDlgLight(CWnd* pParent = nullptr);    // 표준 생성자입니다.
	virtual ~CDlgLight();
	
	void SetScreen(MyScreen* ptr) { m_pScreen = ptr; } // MyScreen 포인터 설정 함수

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	MyScreen* m_pScreen = nullptr; // MyScreen 포인터 멤버

public:
	afx_msg void OnBnClickedLightDefault();
	afx_msg void OnBnClickedLightBright();
	afx_msg void OnBnClickedLightDark();

	afx_msg void OnBnClickedMtlPlastic();
	afx_msg void OnBnClickedMtlMetal();
	afx_msg void OnBnClickedMtlMatte();
};