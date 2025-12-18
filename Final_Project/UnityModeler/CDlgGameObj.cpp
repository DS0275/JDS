// CDlgGameObj.cpp

#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgGameObj.h"
#include "MyScreen.h"        
#include "OglTransform.h"   
#include "Vector3.h"        

IMPLEMENT_DYNAMIC(CDlgGameObj, CDialogEx)

CDlgGameObj::CDlgGameObj(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEOBJ, pParent)
	, m_sGameObjName(_T(""))
	, m_nSelectedIndex(-1)
	, m_nTypeIndex(0) // 기본 Sphere
{
	m_pLbGameObj = nullptr;
	m_pScreen = nullptr;

	// Translate
	m_fTx = m_fTy = m_fTz = 0.f;

	// Rotate
	m_fRx = m_fRy = m_fRz = 0.f;

	// Scale
	m_fSx = m_fSy = m_fSz = 1.f;

	// Color , Alpha 기본값
	m_color = RGB(255, 255, 255);
	m_fAlpha = 1.f;
}

CDlgGameObj::~CDlgGameObj() {}

// 선택된 GameObject index 전달
void CDlgGameObj::SetSelectedIndex(int idx)
{
	if (!m_pScreen) return;

	m_nSelectedIndex = idx;
	OglTransform& ot = m_pScreen->m_arGameObj[idx];

	// 이름
	m_pLbGameObj->GetText(idx, m_sGameObjName);

	// Transform
	m_fTx = ot.m_translate.x;
	m_fTy = ot.m_translate.y;
	m_fTz = ot.m_translate.z;

	m_fRx = ot.m_rotate.x;
	m_fRy = ot.m_rotate.y;
	m_fRz = ot.m_rotate.z;

	m_fSx = ot.m_scale.x;
	m_fSy = ot.m_scale.y;
	m_fSz = ot.m_scale.z;

	// Color / Alpha
	m_color = ot.m_nColor;
	m_fAlpha = ot.m_alpha;
	m_btnColor.SetColor(m_color);

	// ComboBox에 타입 반영
	switch (ot.m_nType)
	{
	case GameObjType::SPHERE:   m_nTypeIndex = 0; break;
	case GameObjType::CUBE:     m_nTypeIndex = 1; break;
	case GameObjType::CYLINDER: m_nTypeIndex = 2; break;
	default: m_nTypeIndex = 1; break;
	}

	// ComboBox가 초기화되지 않았으면 SetCurSel 호출하지 않음
	if (m_cmbType.GetSafeHwnd())
	{
		m_cmbType.ResetContent();           // 기존 항목 삭제
		m_cmbType.AddString(_T("Sphere"));
		m_cmbType.AddString(_T("Cube"));
		m_cmbType.AddString(_T("Cylinder"));
		m_cmbType.SetCurSel(m_nTypeIndex); // 올바른 선택값 설정
	}

	UpdateData(FALSE);
}

void CDlgGameObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_sGameObjName);

	// Translate
	DDX_Text(pDX, IDC_EDIT_TX, m_fTx);
	DDX_Text(pDX, IDC_EDIT_TY, m_fTy);
	DDX_Text(pDX, IDC_EDIT_TZ, m_fTz);

	// Rotate
	DDX_Text(pDX, IDC_EDIT_RX, m_fRx);
	DDX_Text(pDX, IDC_EDIT_RY, m_fRy);
	DDX_Text(pDX, IDC_EDIT_RZ, m_fRz);

	// Scale
	DDX_Text(pDX, IDC_EDIT_SX, m_fSx);
	DDX_Text(pDX, IDC_EDIT_SY, m_fSy);
	DDX_Text(pDX, IDC_EDIT_SZ, m_fSz);

	// Color / Alpha
	DDX_Control(pDX, IDC_BTN_COLOR, m_btnColor);
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_fAlpha);

	// ComboBox
	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_CBIndex(pDX, IDC_CMB_TYPE, m_nTypeIndex);
}

BEGIN_MESSAGE_MAP(CDlgGameObj, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGameObj::OnBnClickedButton1)
END_MESSAGE_MAP()

// add game object
void CDlgGameObj::OnBnClickedButton1()
{
	UpdateData(TRUE);

	if (!m_pLbGameObj || !m_pScreen) return;

	OglTransform ot;

	// ComboBox 선택값에서 enum으로 변환
	int nSel = m_cmbType.GetCurSel();
	switch (nSel)
	{
	case 0: ot.m_nType = GameObjType::SPHERE; break;
	case 1: ot.m_nType = GameObjType::CUBE; break;
	case 2: ot.m_nType = GameObjType::CYLINDER; break;
	default: ot.m_nType = GameObjType::CUBE; break;
	}

	// Transform
	ot.m_translate = Vector3(m_fTx, m_fTy, m_fTz);
	ot.m_rotate = Vector3(m_fRx, m_fRy, m_fRz);
	ot.m_scale = Vector3(m_fSx, m_fSy, m_fSz);

	// Color & Alpha
	ot.m_nColor = m_btnColor.GetColor();
	ot.m_alpha = m_fAlpha;

	if (m_nSelectedIndex >= 0)
	{
		m_pScreen->m_arGameObj[m_nSelectedIndex] = ot;
		m_pLbGameObj->DeleteString(m_nSelectedIndex);
		m_pLbGameObj->InsertString(m_nSelectedIndex, m_sGameObjName);
		m_pLbGameObj->SetCurSel(m_nSelectedIndex);
	}
	else
	{
		m_pLbGameObj->AddString(m_sGameObjName);
		m_pScreen->AddGameObject(ot);
	}

	m_pScreen->Invalidate(FALSE);
}

BOOL CDlgGameObj::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Owner Draw 스타일 설정
	m_btnColor.ModifyStyle(0, BS_OWNERDRAW);

	m_btnColor.SetColor(m_color);
	m_btnColor.EnableAutomaticButton(_T("Automatic"), RGB(255, 255, 255));
	m_btnColor.EnableOtherButton(_T("Other"));

	// ComboBox 초기화
	m_cmbType.ResetContent();
	m_cmbType.AddString(_T("Sphere"));   // index 0
	m_cmbType.AddString(_T("Cube"));     // index 1
	m_cmbType.AddString(_T("Cylinder")); // index 2
	m_cmbType.SetCurSel(m_nTypeIndex);

	UpdateData(FALSE);
	return TRUE;
}
