#include "CBY_HeroMove.h"


namespace CBY
{
	void CBY_HeroMove::Process()
	{
		m_pHero->SetState(CHAR_MOVE);

		//SetColDirection();
	
		bool bMove = false;

		if (I_Input.KeyCheck(VK_LBUTTON))
		{
			m_pHero->SetAction(EVENT_ATTACK);
			return;
		}

		if (I_Input.GetKeyCheck(VK_SPACE))
		{
			m_pHero->SetAction(EVENT_JUMP);
			return;
		}

		if (I_Input.GetKeyCheck(VK_SHIFT))
		{
			m_pHero->SetAction(EVENT_RUN);
			return;
		}

		m_vMove = m_pHero->GetHeroPos();
		m_vLook = m_pHero->GetCamera()->m_LookDir;
		m_vSide = m_pHero->GetCamera()->m_SideDir;

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

		if (bMove)
		{
			m_pHero->SetHeroPos(m_vMove);
		}
		else
		{
			m_pHero->SetAction(EVENT_IDLE);
		}
	}

	CBY_HeroMove::CBY_HeroMove(CBY_Hero* host) : CBY_HeroProcess(host)
	{
	}


	CBY_HeroMove::~CBY_HeroMove()
	{
	}
}
