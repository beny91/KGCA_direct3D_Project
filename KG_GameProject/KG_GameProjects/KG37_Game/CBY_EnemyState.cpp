#include "CBY_EnemyState.h"

namespace CBY
{
	void CBY_EnemyState::Input(DWORD Event, DWORD Output)
	{
		m_StateMap[Event] = Output;
	}

	DWORD CBY_EnemyState::Output(DWORD Event)
	{
		return m_StateMap[Event];
	}

	CBY_EnemyState::CBY_EnemyState()
	{
	}


	CBY_EnemyState::~CBY_EnemyState()
	{
	}
}

