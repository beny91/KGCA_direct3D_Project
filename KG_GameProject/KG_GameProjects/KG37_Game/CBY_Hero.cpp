#include "CBY_Hero.h"
#include "CBY_HeroStateStd.h"
#include "CBY_EnemyAi.h"

namespace CBY
{
	bool CBY_Hero::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context)
	{
		return true;
	}

	void CBY_Hero::SetAction(DWORD Event)
	{
		m_dwCharState = CBY_HeroFSM::Get().Output(m_dwCharState, Event);
		m_Action = m_ActionList[m_dwCharState];
	}

	void CBY_Hero::Process()
	{
		m_Action->Process();
		Frame();
	}

	bool CBY_Hero::Init()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Init();
		SetMoveSpeed(10);

		CBY_HeroFSM::Get().Init();

		m_dwCharState = CHAR_IDLE;

		m_ActionList[CHAR_IDLE] = new CBY_HeroIdle(this);
		m_ActionList[CHAR_MOVE] = new CBY_HeroMove(this);
		m_ActionList[CHAR_JUMP] = new CBY_HeroJump(this);
		m_ActionList[CHAR_RUN] = new CBY_HeroRun(this);
		m_ActionList[CHAR_FIRE] = new CBY_HeroFire(this);
		m_ActionList[CHAR_DAMAGE] = new CBY_HeroDamage(this);
		m_ActionList[CHAR_DEATH] = new CBY_HeroDeath(this);

		m_Action = m_ActionList[CHAR_IDLE];
		return true;
	}

	bool CBY_Hero::Frame()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Frame();
		return true;
	}

	bool CBY_Hero::Render()
	{
		if (m_Character == nullptr)
			return false;

		//m_Character->Render();
		m_Character->NonCharacterRender();
		return true;
	}

	bool CBY_Hero::Release()
	{
		if (m_Character == nullptr)
			return false;

		m_Character->Release();
		m_Bullet.Release();
		for (int i = 0; i < CHAR_STATECOUNT; i++)
		{
			delete m_ActionList[i];
		}
		return true;
	}

	CBY_Hero::CBY_Hero()
	{
		
	}


	CBY_Hero::~CBY_Hero()
	{
	}

	void CBY_HeroProcess::SetColDirection()
	{
		float fM = 0;
		D3DXVECTOR3 vN;
		m_vMove = m_pHero->GetHeroPos();
		m_vLookPush = D3DXVECTOR3(0, 0, 0);
		m_vSidePush = D3DXVECTOR3(0, 0, 0);
		m_vLook = m_pHero->GetCamera()->m_LookDir;
		m_vSide = m_pHero->GetCamera()->m_SideDir;

		if (KG_COLLOSION::ChkOBBToOBBAndDirection(m_pHero->GetCharBox(), m_pHero->m_pEnemy->GetCharBox(), vN, fM))
		{
			float fdot = D3DXVec3Dot(&m_pHero->GetCamera()->m_LookDir, &vN);
			if (fdot < 0)
			{
				m_vLookPush = (2 * D3DXVec3Dot(&-m_pHero->GetCamera()->m_LookDir, &vN))
					* vN + m_pHero->GetCamera()->m_LookDir;									//벽밀림
				m_vSidePush = (2 * D3DXVec3Dot(&-m_pHero->GetCamera()->m_SideDir, &vN))
					* vN + m_pHero->GetCamera()->m_SideDir;

				m_vLook = m_pHero->GetCamera()->m_LookDir - vN * (D3DXVec3Dot(&m_pHero->GetCamera()->m_LookDir, &vN));
				m_vSide = m_pHero->GetCamera()->m_SideDir - vN * (D3DXVec3Dot(&m_pHero->GetCamera()->m_SideDir, &vN));

				m_vMove += m_vLookPush * (fM + 2)*g_SecondTime;
			}
			else
			{
				m_vLookPush = (2 * D3DXVec3Dot(&-m_pHero->GetCamera()->m_LookDir, &vN)) * vN 
					+ m_pHero->GetCamera()->m_LookDir; //벽밀림
				m_vSidePush = (2 * D3DXVec3Dot(&-m_pHero->GetCamera()->m_SideDir, &vN)) * vN 
					+ m_pHero->GetCamera()->m_SideDir;

				m_vLook = m_pHero->GetCamera()->m_LookDir - vN * (D3DXVec3Dot(&m_pHero->GetCamera()->m_LookDir, &vN));
				m_vSide = m_pHero->GetCamera()->m_SideDir - vN * (D3DXVec3Dot(&m_pHero->GetCamera()->m_SideDir, &vN));

				m_vMove -= m_vLookPush * (fM + 2) *g_SecondTime;
			}
		}
	}
}
