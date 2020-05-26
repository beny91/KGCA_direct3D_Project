#include "CBY_EnemyFSM.h"

namespace CBY
{
	bool CBY_EnemyFSM::Init()
	{
		//IDLE
		Input(CHAR_IDLE, EVENT_CREATE, CHAR_IDLE);
		Input(CHAR_IDLE, EVENT_MOVE, CHAR_MOVE);
		Input(CHAR_IDLE, EVENT_JUMP, CHAR_JUMP);
		Input(CHAR_IDLE, EVENT_DAMAGE, CHAR_DAMAGE);
		Input(CHAR_IDLE, EVENT_RUN, CHAR_RUN);
		Input(CHAR_IDLE, EVENT_DEATH, CHAR_DEATH);
		Input(CHAR_IDLE, EVENT_ATTACK, CHAR_FIRE);

		//Move
		Input(CHAR_MOVE, EVENT_ATTACK, CHAR_FIRE);
		Input(CHAR_MOVE, EVENT_JUMP, CHAR_JUMP);
		Input(CHAR_MOVE, EVENT_DAMAGE, CHAR_DAMAGE);
		Input(CHAR_MOVE, EVENT_RUN, CHAR_RUN);
		Input(CHAR_MOVE, EVENT_DEATH, CHAR_DEATH);
		Input(CHAR_MOVE, EVENT_IDLE, CHAR_IDLE);

		//Run
		Input(CHAR_RUN, EVENT_MOVE, CHAR_MOVE);
		Input(CHAR_RUN, EVENT_JUMP, CHAR_JUMP);
		Input(CHAR_RUN, EVENT_IDLE, CHAR_IDLE);
		Input(CHAR_RUN, EVENT_DAMAGE, CHAR_DAMAGE);
		Input(CHAR_RUN, EVENT_DEATH, CHAR_DEATH);
		Input(CHAR_RUN, EVENT_ATTACK, CHAR_FIRE);

		//Jump
		Input(CHAR_JUMP, EVENT_IDLE, CHAR_IDLE);
		Input(CHAR_JUMP, EVENT_DAMAGE, CHAR_DAMAGE);

		//Attack
		Input(CHAR_FIRE, EVENT_IDLE, CHAR_IDLE);
		Input(CHAR_FIRE, EVENT_DAMAGE, CHAR_DAMAGE);
		Input(CHAR_FIRE, EVENT_DEATH, CHAR_DEATH);
		Input(CHAR_FIRE, EVENT_JUMP, CHAR_JUMP);
		Input(CHAR_FIRE, EVENT_MOVE, CHAR_MOVE);
		Input(CHAR_FIRE, EVENT_RUN, CHAR_RUN);

		//Damage
		Input(CHAR_DAMAGE, EVENT_IDLE, CHAR_IDLE);
		Input(CHAR_DAMAGE, EVENT_MOVE, CHAR_MOVE);
		Input(CHAR_DAMAGE, EVENT_RUN, CHAR_RUN);
		Input(CHAR_DAMAGE, EVENT_DEATH, CHAR_DEATH);

		//Death
		Input(CHAR_DEATH, EVENT_CREATE, CHAR_IDLE);

		return true;
	}

	void CBY_EnemyFSM::Input(DWORD State, DWORD Event, DWORD Output)
	{
		CBY_EnemyState* monst = nullptr;

		std::map< DWORD, CBY_EnemyState*>::iterator EnemyIter;
		EnemyIter = m_MapList.find(State);
		if (EnemyIter == m_MapList.end())
		{
			monst = new CBY_EnemyState;
			m_MapList[State] = monst;
		}
		else
		{
			monst = (CBY_EnemyState*)EnemyIter->second;
		}

		monst->Input(Event, Output);

	}

	DWORD CBY_EnemyFSM::Output(DWORD State, DWORD Event)
	{
		CBY_EnemyState* pEnemystate = m_MapList[State];
		return pEnemystate->Output(Event);
	}

	CBY_EnemyFSM::CBY_EnemyFSM()
	{
	}


	CBY_EnemyFSM::~CBY_EnemyFSM()
	{
	}
}

