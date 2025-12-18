// UnityModelerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "UnityModeler.h"
#include "UnityModelerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CUnityModelerDlg::CUnityModelerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITYMODELER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pDlgGameObj = nullptr;
	m_pDlgLight = nullptr;
}

CUnityModelerDlg::~CUnityModelerDlg()
{
	if (m_pDlgGameObj) delete m_pDlgGameObj;
	if (m_pDlgLight) delete m_pDlgLight;
}

void CUnityModelerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	DDX_Control(pDX, IDC_LIST1, m_lbGameObj);
}

void CUnityModelerDlg::OnSelchangeListGameObj()
{
	int nSel = m_lbGameObj.GetCurSel();
	if (nSel == LB_ERR) return;

	if (m_pDlgGameObj)
	{
		m_pDlgGameObj->SetSelectedIndex(nSel);
		m_pDlgGameObj->GetDlgItem(IDC_LIST_GAMEOBJ)->SendMessage(LB_SETCURSEL, nSel);
	}
}

BEGIN_MESSAGE_MAP(CUnityModelerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUnityModelerDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CUnityModelerDlg::OnSelchangeTab1)
END_MESSAGE_MAP()


void CUnityModelerDlg::SetTabCtrl(void)
{
	m_tabCtrl.InsertItem(0, _T("Game Object"));
	m_tabCtrl.InsertItem(1, _T("Light"));
	m_tabCtrl.SetCurSel(0);

	CRect rect;
	m_tabCtrl.GetClientRect(&rect);

	m_pDlgGameObj = new CDlgGameObj;
	m_pDlgGameObj->Create(IDD_GAMEOBJ, &m_tabCtrl);
	m_pDlgGameObj->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgGameObj->ShowWindow(SW_SHOW);

	// IDC_LIST1 (m_lbGameObj) 포인터를 CDlgGameObj::m_pLbSceneList로 전달
	m_pDlgGameObj->SetLbSceneList(&m_lbGameObj);

	// IDC_LIST_GAMEOBJ 포인터를 CDlgGameObj::m_pLbObjList로 전달
	CListBox* pLbObjList = (CListBox*)m_pDlgGameObj->GetDlgItem(IDC_LIST_GAMEOBJ);
	if (pLbObjList)
		m_pDlgGameObj->SetLbObjList(pLbObjList);

	m_pDlgGameObj->SetScreen(&m_screen);

	m_pDlgLight = new CDlgLight;
	m_pDlgLight->Create(IDD_LIGHT, &m_tabCtrl);
	m_pDlgLight->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgLight->ShowWindow(SW_HIDE);
	m_pDlgLight->SetScreen(&m_screen);
}

BOOL CUnityModelerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_screen.Create(IDC_SCREEN, this);
	SetTabCtrl();

	return TRUE;
}

void CUnityModelerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CUnityModelerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CUnityModelerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUnityModelerDlg::OnBnClickedButton1()
{
	m_screen.Invalidate(FALSE);
}

void CUnityModelerDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (pNMHDR->idFrom == IDC_TAB_OPT)
	{
		int nSel = m_tabCtrl.GetCurSel();
		switch (nSel)
		{
		case 0:
			m_pDlgGameObj->ShowWindow(SW_SHOW);
			m_pDlgLight->ShowWindow(SW_HIDE);
			break;
		case 1:
			m_pDlgGameObj->ShowWindow(SW_HIDE);
			m_pDlgLight->ShowWindow(SW_SHOW);
			break;
		}
	}
	*pResult = 0;
}