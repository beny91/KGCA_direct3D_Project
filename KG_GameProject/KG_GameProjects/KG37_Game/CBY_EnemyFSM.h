#pragma once
#include "CBY_EnemyState.h"
#include "CBY_ObjStd.h"

namespace CBY
{
	class CBY_EnemyFSM
	{
	public:
		std::map<DWORD, CBY_EnemyState*>  m_MapList;

	public:
		bool Init();
		void Input(DWORD State, DWORD Event, DWORD Output);
		DWORD Output(DWORD State, DWORD Event);

	public:
		static CBY_EnemyFSM& Get()
		{
			static CBY_EnemyFSM mgr;
			return mgr;
		}

	public:
		CBY_EnemyFSM();
		virtual ~CBY_EnemyFSM();
	};
}


