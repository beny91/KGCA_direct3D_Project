#include "CBY_HeroJump.h"

namespace CBY
{
	void CBY_HeroJump::Process()
	{
		m_pHero->SetState(CHAR_JUMP);

		//SetColDirection();
		

		if (m_pHero->GetStateAnimationEnd(CHAR_JUMP))
		{
			m_pHero->SetAction(EVENT_IDLE);
			return;
		}

		m_vMove = m_pHero->GetHeroPos();
		m_vLook = m_pHero->GetCamera()->m_LookDir;
		m_vSide = m_pHero->GetCamera()->m_SideDir;

		if (I_Input.GetKeyCheck('W'))
		{
			m_vMove += m_vLook * m_pHero->GetMoveSpeed() * g_SecondTime;
		}

		if (I_Input.GetKeyCheck('S'))
		{
			m_vMove -= m_vLook * m_pHero->GetMoveSpeed() * g_SecondTime;
		}

		if (I_Input.GetKeyCheck('A'))
		{
			m_vMove += m_vSide * m_pHero->GetMoveSpeed() * g_SecondTime;
		}

		if (I_Input.GetKeyCheck('D'))
		{
			m_vMove -= m_vSide * m_pHero->GetMoveSpeed() * g_SecondTime;
			
		}
		m_pHero->SetHeroPos(m_vMove);
	}

	CBY_HeroJump::CBY_HeroJump(CBY_Hero* host) : CBY_HeroProcess(host)
	{
	}


	CBY_HeroJump::~CBY_HeroJump()
	{
	}
}
