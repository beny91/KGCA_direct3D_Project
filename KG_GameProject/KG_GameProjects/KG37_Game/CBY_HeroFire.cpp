#include "CBY_HeroFire.h"
#include "CBY_BulletMgr.h"
#include "VFX_ObjMgr.h"

namespace CBY
{
	void CBY_HeroFire::Process()
	{
		m_pHero->SetState(CHAR_FIRE);

		SetColDirection();
		

		bool bFire = false;
		bool bMove = false;
		if (I_Input.KeyCheck(VK_LBUTTON))
		{
			/*if (m_pHero->GetFire(CBY::CHAR_FIRE))
			{
				obj1 = VFX_MGR->find(VFX_EFFECT_GUN_SHOT);

				D3DXVECTOR3 pos = m_pHero->GetFirePos(0);
				D3DXVECTOR3 dir = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

				obj1->Execute(pos);

				CBY::CBY_CHAR_BULLET.BulletMake(m_pHero->GetBullet(), m_pHero->GetFirePos(0),
					m_pHero->GetCamera()->m_LookDir, &m_pHero->GetCamera()->m_World);
			}*/

			m_fFireTime += g_SecondTime;
			if (m_fFireTime > 0.2f)
			{
				CBY::CBY_CHAR_BULLET.BulletMake(m_pHero->GetBullet(), m_pHero->GetFirePos(0),
					m_pHero->GetCamera()->m_LookDir, &m_pHero->GetCamera()->m_World);
				m_fFireTime = 0.0f;
			}
			
			bFire = true;
		}

		if (I_Input.GetKeyCheck(VK_SPACE))
		{
			m_pHero->SetAction(EVENT_JUMP);
			m_fFireTime = 0.0f;
			return;
		}

		if (I_Input.GetKeyCheck(VK_SHIFT))
		{
			m_pHero->SetAction(EVENT_RUN);
			m_fFireTime = 0.0f;
			return;
		}

		if (I_Input.GetKeyCheck('W'))
		{
			m_vMove += m_vLook * m_pHero->GetMoveSpeed() * g_SecondTime;
			bMove = true;
		}

		if (I_Input.GetKeyCheck('S'))
		{
			m_vMove -= m_vLook * m_pHero->GetMoveSpeed() * g_SecondTime;
			bMove = true;
		}

		if (I_Input.GetKeyCheck('A'))
		{
			m_vMove += m_vSide * m_pHero->GetMoveSpeed() * g_SecondTime;
			bMove = true;
		}

		if (I_Input.GetKeyCheck('D'))
		{
			m_vMove -= m_vSide * m_pHero->GetMoveSpeed() * g_SecondTime;
			bMove = true;
		}

		if (bFire)
		{
			m_pHero->SetHeroPos(m_vMove);
			return;

		}
		else if( bMove && !bFire)
		{
			m_pHero->SetHeroPos(m_vMove);
			m_fFireTime = 0.0f;
			m_pHero->SetAction(EVENT_MOVE);
			return;
		}
		else
		{
			m_fFireTime = 0.0f;
			m_pHero->SetAction(EVENT_IDLE);
		}
	}

	CBY_HeroFire::CBY_HeroFire(CBY_Hero* host) : CBY_HeroProcess(host)
	{
		m_fFireTime = 0.0f;
	}


	CBY_HeroFire::~CBY_HeroFire()
	{
	}
}
