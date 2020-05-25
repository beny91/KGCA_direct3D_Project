#pragma once
#include "CBY_Hero.h"

namespace CBY
{
	class CBY_HeroIdle : public CBY_HeroProcess
	{
	public:
		void Process()override;

	public:
		CBY_HeroIdle(CBY_Hero* host);
		virtual ~CBY_HeroIdle();
	};
}

