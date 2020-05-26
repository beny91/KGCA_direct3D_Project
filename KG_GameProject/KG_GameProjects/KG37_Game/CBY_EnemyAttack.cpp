#include "CBY_EnemyAttack.h"


namespace CBY
{
	void CBY_EnemyAttack::Process()
	{
		m_pEnemy->SetState(CHAR_FIRE);

		//SetColDirection();

		if (m_pEnemy->GetStateAnimationEnd(CHAR_FIRE))
		{
			m_pEnemy->SetAction(EVENT_RUN);
		}
	}

	CBY_EnemyAttack::CBY_EnemyAttack(CBY_EnemyAi* host) : CBY_EnemyProcess(host)
	{
	}


	CBY_EnemyAttack::~CBY_EnemyAttack()
	{
	}
}
