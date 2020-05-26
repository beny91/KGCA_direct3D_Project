#include "CBY_HeroRun.h"


namespace CBY
{
	void CBY_HeroRun::Process()
	{
		m_pHero->SetState(CHAR_RUN);

		//SetColDirection();
		

		bool bRun = false;
		bool bMove = false;

		if (I_Input.GetKeyCheck(VK_SPACE))
		{
			m_pHero->SetAction(EVENT_JUMP);
			return;
		}

		if (I_Input.GetKeyCheck(VK_SHIFT))
		{
			bRun = true;
		}

		m_vMove = m_pHero->GetHeroPos();
		m_vLook = m_pHero->GetCamera()->m_LookDir;
		m_vSide = m_pHero->GetCamera()->m_SideDir;

		if (I_Input.GetKeyCheck('W'))
		{
			m_vMove += m_vLook * (m_pHero->GetMoveSpeed()+10) * g_SecondTime;
			if (!bRun)
			{
				m_pHero->SetAction(EVENT_MOVE);
			}
			bMove = true;
			
		}

		if (I_Input.GetKeyCheck('S'))
		{
			m_vMove -= m_vLook * (m_pHero->GetMoveSpeed() + 10) * g_SecondTime;
			if (!bRun)
			{
				m_pHero->SetAction(EVENT_MOVE);
			}
			bMove = true;
			
		}

		if (I_Input.GetKeyCheck('A'))
		{
			m_vMove += m_vSide * (m_pHero->GetMoveSpeed() + 10) * g_SecondTime;
			if (!bRun)
			{
				m_pHero->SetAction(EVENT_MOVE);
			}
			bMove = true;
		}

		if (I_Input.GetKeyCheck('D'))
		{
			m_vMove -= m_vSide * (m_pHero->GetMoveSpeed() + 10) * g_SecondTime;
			if (!bRun)
			{
				m_pHero->SetAction(EVENT_MOVE);
			}
			bMove = true;
		}

		if (bRun || bMove)
		{
			m_pHero->SetHeroPos(m_vMove);
		}
		else
		{
			m_pHero->SetAction(EVENT_IDLE);
		}
	}

	CBY_HeroRun::CBY_HeroRun(CBY_Hero* host) : CBY_HeroProcess(host)
	{
	}


	CBY_HeroRun::~CBY_HeroRun()
	{
	}
}
