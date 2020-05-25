#include "CBY_HeroIdle.h"

namespace CBY
{
	void CBY_HeroIdle::Process()
	{
		m_pHero->SetState(CBY::CHAR_IDLE);

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

		if (I_Input.KeyCheck(VK_LBUTTON))
		{
			m_pHero->SetAction(EVENT_ATTACK);
			return;
		}

		if (I_Input.GetKeyCheck('W'))
		{
			m_pHero->SetAction(EVENT_MOVE);
			return;
		}

		if (I_Input.GetKeyCheck('S'))
		{
			m_pHero->SetAction(EVENT_MOVE);
			return;
		}

		if (I_Input.GetKeyCheck('A'))
		{
			m_pHero->SetAction(EVENT_MOVE);
			return;
		}

		if (I_Input.GetKeyCheck('D'))
		{
			m_pHero->SetAction(EVENT_MOVE);
			return;
		}

	}

	CBY_HeroIdle::CBY_HeroIdle(CBY_Hero* host) : CBY_HeroProcess(host)
	{
	}


	CBY_HeroIdle::~CBY_HeroIdle()
	{
	}
}
