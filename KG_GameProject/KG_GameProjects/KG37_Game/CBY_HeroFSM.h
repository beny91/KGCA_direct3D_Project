#pragma once
#include "CBY_HeroState.h"
#include "CBY_ObjStd.h"

namespace CBY
{
	class CBY_HeroFSM
	{
	public:
		std::map<DWORD, CBY_HeroState*>  m_MapList;

	public:
		bool Init();
		void Input(DWORD State, DWORD Event, DWORD Output);
		DWORD Output(DWORD State, DWORD Event);

	public:
		static CBY_HeroFSM& Get()
		{
			static CBY_HeroFSM mgr;
			return mgr;
		}

	public:
		CBY_HeroFSM();
		virtual ~CBY_HeroFSM();
	};
}

