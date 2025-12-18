#pragma once
#include "afxdialogex.h"
#include "afxcolorbutton.h"


class MyScreen;

// CDlgGameObj 대화 상자

class CDlgGameObj : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGameObj)

public:
	CDlgGameObj(CWnd* pParent = nullptr);
	virtual ~CDlgGameObj();

	// Scene List (IDC_LIST1) 포인터를 받음
	void SetLbSceneList(CListBox* ptr) { m_pLbSceneList = ptr; }
	// GameObj Dialog 내의 List (IDC_LIST_GAMEOBJ) 포인터를 받음
	void SetLbObjList(CListBox* ptr) { m_pLbObjList = ptr; }
	void SetScreen(MyScreen* ptr) { m_pScreen = ptr; }

	// Scene 리스트에서 선택된 index 전달용
	void SetSelectedIndex(int idx);

	CListBox* m_pLbSceneList;
	CListBox* m_pLbObjList;
	MyScreen* m_pScreen;

	// Note: m_pLbGameObj 멤버는 사용되지 않으므로 제거하거나 무시합니다. (기존 코드에 있던 부분은 제거)

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	int m_nSelectedIndex;
	int m_nTypeIndex;

	CComboBox m_cmbType;
	COLORREF m_bgColor;
	afx_msg void OnBnClickedBgColor();
	afx_msg void OnLbnSelchangeListGameObj();
	afx_msg void OnBnClickedBtnGrid();

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
	afx_msg void OnBnClickedBtnAnim();
	afx_msg void OnBnClickedBtnGrid2();
	afx_msg void OnBnClickedBtnAnim1();
};