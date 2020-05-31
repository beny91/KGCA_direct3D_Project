#include "CBY_Enemy.h"
#include "CBY_BulletMgr.h"
#include "KG_Collision.h"
#include "MyEffectParser.h"
#include "VFX_ObjMgr.h"

namespace CBY
{
	bool CBY_Enemy::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)
	{

		return true;
	}

	bool CBY_Enemy::Init()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Init();
		D3DXVECTOR3 scale = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		obj2 = VFX_MGR->find(VFX_EFFECT_TYPE::VFX_EFFECT_GUN1_SHOT);
		obj2->SetScale(scale);
		return true;
	}

	bool CBY_Enemy::Frame()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Frame();

		if (GetStateAnimationEnd(CBY::CHAR_FIRE))
		{
			SetState(CBY::CHAR_IDLE);
		}

		for (int i = 0; i < CBY_CHAR_BULLET.GetBulletNum(); i++)
		{
			KG_Box AmmoBox = CBY_CHAR_BULLET.GetBulletBox(i);

			if (KG_COLLOSION::ChkOBBToOBB(m_Character->GetCharBox(), AmmoBox))
			{
				for (int ibox = 0; ibox < m_Character->GetColBoxSize(); ibox++)
				{
					if (KG_COLLOSION::ChkOBBToOBB(m_Character->GetColBox(ibox), AmmoBox))
					{
						//KG_Box box = m_Character->GetCharBox();
						CBY_CHAR_BULLET.BulletPop(i);
						SetState(CBY::CHAR_FIRE);
						D3DXVECTOR3 zpos = D3DXVECTOR3(0, 0, 0);
						zpos -= m_pCamera->m_LookDir * 2;
						//zpos += box.vAxis[2] * 2;
						obj2 = VFX_MGR->find(VFX_EFFECT_TYPE::VFX_EFFECT_GUN1_SHOT);
						D3DXVECTOR3 pos = m_Character->GetColPos(ibox);
						pos += zpos;
						//D3DXVECTOR3 dir = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

						obj2->Execute(pos);
						i--;
						break;
					}
				}
			}
		}
		return true;
	}

	bool CBY_Enemy::Render()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Render();
		return true;
	}

	bool CBY_Enemy::Release()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Release();
		return true;
	}
	/////////////Set////////////
	void CBY_Enemy::SetState(int i)
	{
		if (m_Character == nullptr)
			return;

		m_Character->SetState(i);
	}

	void CBY_Enemy::SetMatrix(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
	{
		if (m_Character == nullptr)
			return;

		m_Character->SetMatrix(world, view, proj);
	}
	void CBY_Enemy::SetFireTime(float ftime)
	{
		m_fFireSetTime = ftime;
	}
	void CBY_Enemy::SetCamera(KG_Camera* pcamera)
	{
		m_pCamera = pcamera;
	}

	//////////// Get//////////////
	KG_Box CBY_Enemy::GetCharBox()
	{
		if (m_Character == nullptr)
			return KG_Box();

		return m_Character->GetCharBox();
	}

	D3DXVECTOR3 CBY_Enemy::GetFirePos(int i)
	{
		if (m_Character == nullptr)
			return D3DXVECTOR3(0, 0, 0);

		return m_Character->GetFirePos(i);
	}

	bool CBY_Enemy::GetStateAnimationStart(int i)
	{
		if (m_Character == nullptr)
			return false;

		return m_Character->GetStateAnimationStart(i);
	}

	bool CBY_Enemy::GetStateAnimationEnd(int i)
	{
		if (m_Character == nullptr)
			return false;

		return m_Character->GetStateAnimationEnd(i);
	}


	bool CBY_Enemy::GetFire(int i)
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

	CBY_Bullet* CBY_Enemy::GetBullet()
	{
		if (m_Character == nullptr)
			return nullptr;

		return &m_Bullet;
	}

	CBY_Enemy::CBY_Enemy()
	{
		m_fFireSetTime = 0;
		m_fFireTime = 0;
		m_bFireTime = false;
	}


	CBY_Enemy::~CBY_Enemy()
	{
	}
}

