#pragma once
#include "afxdialogex.h"
#include "afxcolorbutton.h"


class MyScreen; // 전방 선언

// CDlgGameObj 대화 상자

class CDlgGameObj : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGameObj)

public:
	CDlgGameObj(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgGameObj();

	void SetLbGameObj(CListBox* ptr) { m_pLbGameObj = ptr; }
	void SetScreen(MyScreen* ptr) { m_pScreen = ptr; }

	// Scene 리스트에서 선택된 index 전달용
	void SetSelectedIndex(int idx);

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOBJ };
#endif

protected:
	CListBox* m_pLbGameObj; // list box for game objects
	MyScreen* m_pScreen;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	int m_nSelectedIndex;	//  Scene 선택 index
	int m_nTypeIndex;       // ComboBox 선택 index

	CComboBox m_cmbType;    // ComboBox 컨트롤 변수

public:
	CString m_sGameObjName;


	// Translate
	float m_fTx;
	float m_fTy;
	float m_fTz;

	// Rotate
	float m_fRx;
	float m_fRy;
	float m_fRz;

	// Scale
	float m_fSx;
	float m_fSy;
	float m_fSz;

	afx_msg void OnBnClickedButton1();

	// Color & Alpha
	CMFCColorButton m_btnColor;
	COLORREF m_color;
	float m_fAlpha;
};
