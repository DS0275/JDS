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
	, m_nTypeIndex(0)
{
	m_pLbSceneList = nullptr;
	m_pLbObjList = nullptr;
	m_pScreen = nullptr;

	m_fTx = m_fTy = m_fTz = 0.f;

	m_fRx = m_fRy = m_fRz = 0.f;

	m_fSx = m_fSy = m_fSz = 1.f;

	m_color = RGB(255, 255, 255);
	m_fAlpha = 1.f;

	m_bgColor = RGB(30, 30, 30);
}

CDlgGameObj::~CDlgGameObj() {}

void CDlgGameObj::SetSelectedIndex(int idx)
{
	if (!m_pScreen || !m_pLbSceneList) return;

	m_nSelectedIndex = idx;
	OglTransform& ot = m_pScreen->m_arGameObj[idx];

	m_pLbSceneList->GetText(idx, m_sGameObjName);

	m_fTx = ot.m_translate.x;
	m_fTy = ot.m_translate.y;
	m_fTz = ot.m_translate.z;

	m_fRx = ot.m_rotate.x;
	m_fRy = ot.m_rotate.y;
	m_fRz = ot.m_rotate.z;

	m_fSx = ot.m_scale.x;
	m_fSy = ot.m_scale.y;
	m_fSz = ot.m_scale.z;

	m_color = ot.m_nColor;
	m_fAlpha = ot.m_alpha;
	m_btnColor.SetColor(m_color);

	switch (ot.m_nType)
	{
	case GameObjType::SPHERE:    m_nTypeIndex = 0; break;
	case GameObjType::CUBE:      m_nTypeIndex = 1; break;
	case GameObjType::CYLINDER: m_nTypeIndex = 2; break;
	case GameObjType::QUAD:      m_nTypeIndex = 3; break;
	case GameObjType::TRI:       m_nTypeIndex = 4; break;
	case GameObjType::PLANE:     m_nTypeIndex = 5; break;
	case GameObjType::CAPSULE:   m_nTypeIndex = 6; break;
	default: m_nTypeIndex = 0; break;
	}

	if (m_cmbType.GetSafeHwnd())
	{
		m_cmbType.SetCurSel(m_nTypeIndex);
	}

	UpdateData(FALSE);
}

void CDlgGameObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_sGameObjName);

	DDX_Text(pDX, IDC_EDIT_TX, m_fTx);
	DDX_Text(pDX, IDC_EDIT_TY, m_fTy);
	DDX_Text(pDX, IDC_EDIT_TZ, m_fTz);

	DDX_Text(pDX, IDC_EDIT_RX, m_fRx);
	DDX_Text(pDX, IDC_EDIT_RY, m_fRy);
	DDX_Text(pDX, IDC_EDIT_RZ, m_fRz);

	DDX_Text(pDX, IDC_EDIT_SX, m_fSx);
	DDX_Text(pDX, IDC_EDIT_SY, m_fSy);
	DDX_Text(pDX, IDC_EDIT_SZ, m_fSz);

	DDX_Control(pDX, IDC_BTN_COLOR, m_btnColor);
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_fAlpha);

	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_CBIndex(pDX, IDC_CMB_TYPE, m_nTypeIndex);
}

BEGIN_MESSAGE_MAP(CDlgGameObj, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGameObj::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_BG_COLOR, &CDlgGameObj::OnBnClickedBgColor)
	ON_LBN_SELCHANGE(IDC_LIST_GAMEOBJ, &CDlgGameObj::OnLbnSelchangeListGameObj)
	ON_BN_CLICKED(IDC_BTN_GRID, &CDlgGameObj::OnBnClickedBtnGrid)
	ON_BN_CLICKED(IDC_BTN_ANIM1, &CDlgGameObj::OnBnClickedBtnAnim1)
END_MESSAGE_MAP()


void CDlgGameObj::OnBnClickedButton1()
{
	UpdateData(TRUE);

	if (!m_pLbSceneList || !m_pScreen) return;

	OglTransform ot;

	int nSel = m_cmbType.GetCurSel();
	switch (nSel)
	{
	case 0: ot.m_nType = GameObjType::SPHERE;	break;
	case 1: ot.m_nType = GameObjType::CUBE;		break;
	case 2: ot.m_nType = GameObjType::CYLINDER; break;
	case 3: ot.m_nType = GameObjType::QUAD;		break;
	case 4: ot.m_nType = GameObjType::TRI;		break;
	case 5: ot.m_nType = GameObjType::PLANE;	break;
	case 6: ot.m_nType = GameObjType::CAPSULE;	break;
	default: ot.m_nType = GameObjType::CUBE;	break;
	}

	ot.m_translate = Vector3(m_fTx, m_fTy, m_fTz);
	ot.m_rotate = Vector3(m_fRx, m_fRy, m_fRz);
	ot.m_scale = Vector3(m_fSx, m_fSy, m_fSz);

	ot.m_nColor = m_btnColor.GetColor();
	ot.m_alpha = m_fAlpha;

	if (m_nSelectedIndex >= 0)
	{
		m_pScreen->m_arGameObj[m_nSelectedIndex] = ot;

		// Scene List 갱신
		m_pLbSceneList->DeleteString(m_nSelectedIndex);
		m_pLbSceneList->InsertString(m_nSelectedIndex, m_sGameObjName);
		m_pLbSceneList->SetCurSel(m_nSelectedIndex);

		if (m_pLbObjList)
		{
			m_pLbObjList->DeleteString(m_nSelectedIndex);
			m_pLbObjList->InsertString(m_nSelectedIndex, m_sGameObjName);
		}
	}
	else
	{
		m_pScreen->AddGameObject(ot);

		// Scene 리스트에 추가
		m_pLbSceneList->AddString(m_sGameObjName);

		// OBJ List에 추가
		if (m_pLbObjList)
			m_pLbObjList->AddString(m_sGameObjName);
	}

	if (m_pScreen)
		m_pScreen->Invalidate(FALSE);
}

BOOL CDlgGameObj::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btnColor.ModifyStyle(0, BS_OWNERDRAW);

	m_btnColor.SetColor(m_color);
	m_btnColor.EnableAutomaticButton(_T("Automatic"), RGB(255, 255, 255));
	m_btnColor.EnableOtherButton(_T("Other"));

	m_cmbType.ResetContent();
	m_cmbType.AddString(_T("Sphere"));
	m_cmbType.AddString(_T("Cube"));
	m_cmbType.AddString(_T("Cylinder"));
	m_cmbType.AddString(_T("Quad"));
	m_cmbType.AddString(_T("Tri"));
	m_cmbType.AddString(_T("Plane"));
	m_cmbType.AddString(_T("Capsule"));
	m_cmbType.SetCurSel(m_nTypeIndex);

	UpdateData(FALSE);
	return TRUE;
}

void CDlgGameObj::OnBnClickedBgColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK) return;

	COLORREF c = dlg.GetColor();

	float r = GetRValue(c) / 255.f;
	float g = GetGValue(c) / 255.f;
	float b = GetBValue(c) / 255.f;

	m_pScreen->SetBackgroundColor(r, g, b, 1.0f);

	m_pScreen->Invalidate(FALSE);
}

void CDlgGameObj::OnLbnSelchangeListGameObj()
{
	if (!m_pLbObjList || !m_pScreen) return;

	int idx = m_pLbObjList->GetCurSel();
	if (idx < 0) return;

	m_pScreen->m_nSelectedObjIndex = idx;

	// UI 갱신
	SetSelectedIndex(idx);

	// 다시 그리기
	m_pScreen->Invalidate(FALSE);
}

void CDlgGameObj::OnBnClickedBtnGrid()
{
	if (!m_pScreen) return;

	m_pScreen->m_bShowGrid = !m_pScreen->m_bShowGrid;
	m_pScreen->Invalidate(FALSE);
}

void CDlgGameObj::OnBnClickedBtnAnim1()
{
	if (!m_pScreen) return;

	m_pScreen->m_bAnimOn = !m_pScreen->m_bAnimOn;
	m_pScreen->Invalidate(FALSE);
}
