#include "KG37_GameMain.h"

bool KG37_GameMain::Init()
{
	CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pAlpahBlend);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSampler);
	CDX::ApplyRS(m_pContext, CDX::KG_DxState::g_pRSSold);

	m_Character = std::make_shared<CBY::CBY_Character>();
	m_Character->CharacterLoad(m_pd3dDevice, m_pContext, L"../../data/char/save/GirlInfo.txt");

	m_CharCamera = std::make_shared<CBY::CBY_CharacterCamera>();
	m_CharCamera->SetViewProj();
	m_CharCamera->SetCameraSpeed(30);
	m_pMainCamera = m_CharCamera.get();
	return true;
}

bool KG37_GameMain::Frame()
{
	if (m_Character == nullptr)return true;
	bool bClick = false;
	if (I_Input.GetKeyCheck(VK_SHIFT))
	{
		m_Character->SetState(CBY::CHAR_RUN);
		bClick = true;
	}

	if (I_Input.GetKeyCheck('W'))
	{
		m_Character->SetState(CBY::CHAR_MOVE);
		bClick = true;
	}
	if (I_Input.GetKeyCheck('S'))
	{
		m_Character->SetState(CBY::CHAR_MOVE);
		bClick = true;
	}
	if (I_Input.GetKeyCheck('A'))
	{
		m_Character->SetState(CBY::CHAR_MOVE);
		bClick = true;
	}
	if (I_Input.GetKeyCheck('D'))
	{
		m_Character->SetState(CBY::CHAR_MOVE);
		bClick = true;
	}

	if (I_Input.GetKeyCheck(VK_SPACE))
	{
		m_Character->SetState(CBY::CHAR_JUMP);
		bClick = true;
	}

	if (!bClick)
	{
		m_Character->SetState(CBY::CHAR_IDLE);
	}

	m_Character->Frame();
	D3DXMATRIX zpos;
	D3DXMatrixIdentity(&zpos);
	zpos._42 = 20;
	zpos._43 = -30;
	D3DXMATRIX charmat = m_Character->m_pMatrixList[46] * zpos * m_Character->m_matWorld;
	D3DXVECTOR3 bonepos = D3DXVECTOR3(charmat._41, charmat._42, charmat._43);
	m_pMainCamera->m_Pos = bonepos;
	return true;
}

bool KG37_GameMain::Render()
{
	CDX::ApplyBS(m_pContext, CDX::KG_DxState::g_pAlpahBlend);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSampler, 0);
	CDX::ApplySS(m_pContext, CDX::KG_DxState::g_pSSClampLinear, 1);


	m_Character->SetMatrix(&(m_pMainCamera->m_World), &m_pMainCamera->m_View, &m_pMainCamera->m_Proj);
	m_Character->Render();
	return true;
}

bool KG37_GameMain::Release()
{
	m_Character->Release();
	m_CharCamera->Release();

	return true;
}

KG37_GameMain::KG37_GameMain()
{
}


KG37_GameMain::~KG37_GameMain()
{
}
