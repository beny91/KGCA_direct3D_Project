#include "CBY_EnemyDeath.h"


namespace CBY
{
	void CBY_EnemyDeath::Process()
	{
		m_pEnemy->SetState(CHAR_DEATH);
		if (m_pEnemy->GetStateAnimationEnd(CHAR_DEATH))
		{
			m_pEnemy->SetEndClip(CHAR_DEATH, true);
		}
	}

	CBY_EnemyDeath::CBY_EnemyDeath(CBY_EnemyAi* host) : CBY_EnemyProcess(host)
	{
	}


	CBY_EnemyDeath::~CBY_EnemyDeath()
	{
	}
}
