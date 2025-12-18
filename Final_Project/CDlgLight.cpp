#include "pch.h"
#include "resource.h"
#include "CDlgLight.h"
#include "MyScreen.h"
#include "MaterialPreset.h"
#include "LightPreset.h"

IMPLEMENT_DYNAMIC(CDlgLight, CDialogEx)

CDlgLight::CDlgLight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIGHT, pParent)
{
}

CDlgLight::~CDlgLight()
{
}

void CDlgLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgLight, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LIGHT_DEFAULT, &CDlgLight::OnBnClickedLightDefault)
	ON_BN_CLICKED(IDC_BTN_LIGHT_BRIGHT, &CDlgLight::OnBnClickedLightBright)
	ON_BN_CLICKED(IDC_BTN_LIGHT_DARK, &CDlgLight::OnBnClickedLightDark)

	ON_BN_CLICKED(IDC_BTN_MTL_PLASTIC, &CDlgLight::OnBnClickedMtlPlastic)
	ON_BN_CLICKED(IDC_BTN_MTL_METAL, &CDlgLight::OnBnClickedMtlMetal)
	ON_BN_CLICKED(IDC_BTN_MTL_MATTE, &CDlgLight::OnBnClickedMtlMatte)
END_MESSAGE_MAP()

void CDlgLight::OnBnClickedLightDefault()
{
	if (!m_pScreen) return;

	m_pScreen->m_lightMtl.ApplyLightPreset(LightPreset::DEFAULT);
	m_pScreen->m_curLightPreset = LightPreset::DEFAULT;

	m_pScreen->Invalidate(FALSE);
}

void CDlgLight::OnBnClickedLightBright()
{
	if (!m_pScreen) return;

	m_pScreen->m_lightMtl.ApplyLightPreset(LightPreset::BRIGHT);
	m_pScreen->m_curLightPreset = LightPreset::BRIGHT;

	m_pScreen->Invalidate(FALSE);
}

void CDlgLight::OnBnClickedLightDark()
{
	if (!m_pScreen) return;

	m_pScreen->m_lightMtl.ApplyLightPreset(LightPreset::DARK);
	m_pScreen->m_curLightPreset = LightPreset::DARK;

	m_pScreen->Invalidate(FALSE);
}


void CDlgLight::OnBnClickedMtlPlastic()
{
	if (!m_pScreen) return;
	m_pScreen->m_lightMtl.ApplyMaterialPreset(MaterialPreset::PLASTIC);
	m_pScreen->Invalidate(FALSE);
}

void CDlgLight::OnBnClickedMtlMetal()
{
	if (!m_pScreen) return;
	m_pScreen->m_lightMtl.ApplyMaterialPreset(MaterialPreset::METAL);
	m_pScreen->Invalidate(FALSE);
}

void CDlgLight::OnBnClickedMtlMatte()
{
	if (!m_pScreen) return;
	m_pScreen->m_lightMtl.ApplyMaterialPreset(MaterialPreset::MATTE);
	m_pScreen->Invalidate(FALSE);
}
