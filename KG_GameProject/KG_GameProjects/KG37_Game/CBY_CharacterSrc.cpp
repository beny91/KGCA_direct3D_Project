#include "CBY_CharacterSrc.h"


namespace CBY
{
	bool CBY_CharacterSrc::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)
	{
		return true;
	}

	bool CBY_CharacterSrc::Init()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Init();
		return true;
	}

	bool CBY_CharacterSrc::Frame()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Frame();
		return true;
	}

	bool CBY_CharacterSrc::Render()
	{
		if (m_Character == nullptr)
			return false;

		//m_Character->Render();
		m_Character->NonCharacterRender();
		return true;
	}

	bool CBY_CharacterSrc::Release()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Release();
		m_Bullet.Release();
		return true;
	}
	/////////////Set////////////
	void CBY_CharacterSrc::SetState(int i)
	{
		if (m_Character == nullptr)
			return;

		m_Character->SetState(i);
	}

	void CBY_CharacterSrc::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
	{
		if (m_Character == nullptr)
			return;

		world->_41 = m_vCharPos.x;
		world->_42 = m_vCharPos.y;
		world->_43 = m_vCharPos.z;
		m_Character->SetMatrix(world, view, proj);
	}
	void CBY_CharacterSrc::SetFireTime(float ftime)
	{
		m_fFireSetTime = ftime;
	}
	void CBY_CharacterSrc::SetHeroPos(D3DXVECTOR3 vpos)
	{
		m_vCharPos = vpos;
	}

	//////////// Get//////////////
	D3DXVECTOR3 CBY_CharacterSrc::GetCamerPos()
	{
		if (m_Character == nullptr)
			return D3DXVECTOR3(0, 0, 0);

		D3DXMATRIX zpos;
		D3DXMatrixIdentity(&zpos);
		zpos._42 = 20;
		zpos._43 = -30;
		D3DXMATRIX charmat = m_Character->m_pMatrixList[46] * zpos * m_Character->m_matWorld;
		D3DXVECTOR3 bonepos = D3DXVECTOR3(charmat._41, charmat._42, charmat._43);

		return bonepos;
	}

	KG_Box CBY_CharacterSrc::GetCharBox()
	{
		if (m_Character == nullptr)
			return KG_Box();

		return m_Character->GetCharBox();
	}

	KG_Box CBY_CharacterSrc::GetColBox(int ibox)
	{
		return m_Character->GetColBox(ibox);
	}
	
	D3DXVECTOR3 CBY_CharacterSrc::GetColPos(int ibox)
	{
		return m_Character->GetColPos(ibox);
	}

	int CBY_CharacterSrc::GetColBoxSize()
	{
		return m_Character->GetColBoxSize();
	}

	D3DXVECTOR3 CBY_CharacterSrc::GetFirePos(int i)
	{
		if (m_Character == nullptr)
			return D3DXVECTOR3(0, 0, 0);

		return m_Character->GetFirePos(i);
	}

	bool CBY_CharacterSrc::GetStateAnimationStart(int i)
	{
		if (m_Character == nullptr)
			return false;

		return m_Character->GetStateAnimationStart(i);
	}

	bool CBY_CharacterSrc::GetStateAnimationEnd(int i)
	{
		if (m_Character == nullptr)
			return false;

		return m_Character->GetStateAnimationEnd(i);
	}


	bool CBY_CharacterSrc::GetFire(int i)
	{
		if (m_Character == nullptr)
			return false;

		if (GetStateAnimationStart(i))
		{
			m_bFireTime = true;
			m_fFireTime = 0.0;
		}

		if (m_bFireTime)
		{
			m_fFireTime += g_SecondTime;
		}

		if (m_fFireTime > m_fFireSetTime)
		{
			m_fFireTime = 0.0f;
			m_bFireTime = false;
			return true;
		}

		return false;
	}

	D3DXVECTOR3 CBY_CharacterSrc::GetHeroPos()
	{
		return m_vCharPos;
	}

	CBY_Bullet* CBY_CharacterSrc::GetBullet()
	{
		if (m_Character == nullptr)
			return nullptr;

		return &m_Bullet;
	}

	CBY_CharacterSrc::CBY_CharacterSrc()
	{
		m_fFireSetTime = 0;
		m_fFireTime = 0;
		m_bFireTime = false;
		m_fSpeed = 0;
		m_vCharPos = D3DXVECTOR3(0, 0, 0);
	}


	CBY_CharacterSrc::~CBY_CharacterSrc()
	{
	}
}
