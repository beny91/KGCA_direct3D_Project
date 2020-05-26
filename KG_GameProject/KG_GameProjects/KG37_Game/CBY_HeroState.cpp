#include "CBY_HeroState.h"

namespace CBY
{
	void CBY_HeroState::Input(DWORD Event, DWORD Output)
	{
		m_StateMap[Event] = Output;
	}

	DWORD CBY_HeroState::Output(DWORD Event)
	{
		return m_StateMap[Event];
	}

	CBY_HeroState::CBY_HeroState()
	{
	}


	CBY_HeroState::~CBY_HeroState()
	{
	}
}
