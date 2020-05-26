#pragma once
#include "KG_Std.h"
#include "CBY_CharacterStateStd.h"

namespace CBY
{
	class CBY_EnemyState
	{
	public:
		std::map<DWORD, DWORD> m_StateMap;
		DWORD m_State;

	public:
		void Input(DWORD Event, DWORD Output);
		DWORD Output(DWORD Event);

	public:
		CBY_EnemyState();
		virtual ~CBY_EnemyState();
	};
}

